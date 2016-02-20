#include <stdio.h>
#include <string.h>

#include <gtk/gtk.h>
#include <gdk/gdk.h>
#include <directfb.h>

#include <JavaScriptCore/JavaScript.h>

#include <sys/ioctl.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <linux/einkfb.h>

typedef struct WebKitWebSettings WebKitWebSettings;

// forward declaration 
GtkWidget * webkit_web_view_new (void);

char html_file[256];
time_t last_html_file_modification;

GtkWidget *window;
GtkWidget* web;

#include <sys/types.h>
#include <sys/stat.h>

// http://stackoverflow.com/questions/4021479/getting-file-modification-time-on-unix-using-utime-in-c
time_t get_mtime(const char *path) {
    struct stat statbuf;
    if (stat(path, &statbuf) == -1) {
        perror(path);
        // exit(1);
    }
    return statbuf.st_mtime;
}

// http://www.mobileread.com/forums/showthread.php?t=144212
void update_eink(unsigned xx,unsigned yy,unsigned xxx,unsigned yyy) {
    update_area_t data;
    int fd;
    fd = open("/dev/fb0", O_RDWR);
    data.x1 = xx;
    data.y1 = yy;
    data.x2 = 2 + xxx;
    if(600 < data.x2) data.x2 = 600;
    data.y2 = 2 + yyy;
    if(800 < data.y2) data.y2 = 800;
    data.which_fx = fx_update_partial;
    data.buffer = NULL;
    ioctl(fd,FBIO_EINK_UPDATE_DISPLAY_AREA,&data);
    close(fd);
}

void update_eink_full() {
    update_eink(0,0,599,799);
}

gboolean tick(gpointer user_data) {
    GdkWindow *gdk_window = gtk_widget_get_window(GTK_WIDGET(window));
    gdk_window_invalidate_rect(gdk_window, NULL, TRUE);
    gdk_window_process_updates(gdk_window, TRUE);
    
    time_t html_file_modification = get_mtime(html_file);
    if(html_file_modification > last_html_file_modification) {
        last_html_file_modification = html_file_modification;
        webkit_web_view_reload(web);
    }
    
    JSGlobalContextRef js_context = (JSGlobalContextRef)webkit_web_frame_get_global_context(webkit_web_view_get_main_frame (web));
    JSObjectRef js_global = JSContextGetGlobalObject(js_context);
    JSValueRef update_fn =  JSObjectGetProperty(js_context, js_global, JSStringCreateWithUTF8CString("update"), NULL);
    if(!JSValueIsUndefined(js_context, update_fn)) {
        JSObjectCallAsFunction(js_context, JSValueToObject(js_context, update_fn, NULL), NULL, 0, NULL, NULL);
        
    } else {
        printf("Update is undefined\n");
    }

    update_eink_full();
    
    return TRUE;
}

int main( int argc, char *argv[] ) {
    if(argc != 2) {
        printf("Usage: ./home file.html\n");
        return 1;
    }
    
    strncpy(html_file, argv[1], 256);
    last_html_file_modification = get_mtime(html_file);
    
    // DirectFBInit(&argc,&argv);
    // DirectFBSetOption("autoflip-window", NULL);
    // DirectFBSetOption("no-cursor", NULL);
    
    gtk_init (&argc, &argv);
    
    // g_thread_init(NULL);

    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title ( GTK_WINDOW(window) , "L:A_N:application_ID:test");
    gtk_window_set_default_size ( GTK_WINDOW(window) , 600, 800);
    gtk_container_set_border_width (GTK_CONTAINER (window), 0);
    
    web = webkit_web_view_new ();
    gtk_container_add (GTK_CONTAINER (window), web);
    webkit_web_view_open(web, html_file);
    gtk_widget_grab_focus(GTK_WIDGET(web));
    
    WebKitWebSettings *settings = (WebKitWebSettings *)webkit_web_settings_new ();
    g_object_set (G_OBJECT(settings), "enable-file-access-from-file-uris", TRUE, NULL);

    /* Apply the result */
    webkit_web_view_set_settings (web, settings);
    
    // GtkWidget *button;
    // button = gtk_button_new_with_label("Clickable!");
    // gtk_container_add (GTK_CONTAINER (window), button);
    
    // GtkWidget *label;
    // label = gtk_label_new ("");
    // gtk_label_set_markup (GTK_LABEL (label), "<span size='30000'>Hello World!\nمرحبا يا عالم!\nこんにちは世界!\nওহে বিশ্ব!\nहैलो वर्ल्ड!\nಹಲೋ ವರ್ಲ್ಡ್!\n</span>");
    // gtk_container_add (GTK_CONTAINER (window), label);
    
    gtk_widget_show_all (window);
    
    gtk_timeout_add(500, tick, NULL);
    
    gdk_window_set_keep_above(gtk_widget_get_window(GTK_WIDGET(window)), TRUE);
    
    gtk_main();
    
    return 0;
}