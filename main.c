#include <gtk/gtk.h>

static void open_file_dialog(){
    
}

static void activate(GtkApplication *app, gpointer data){
    GtkWidget *window = gtk_application_window_new(app);
    GtkWidget* headerBar = gtk_header_bar_new();
    GtkWidget *createPasswordButton = gtk_button_new_with_label("Create Password");
    GtkWidget *mainUIBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 3);
    GtkWidget *listBox = gtk_list_box_new();
    GtkWidget *listBoxRow = gtk_list_box_row_new();
    gtk_box_append(GTK_BOX(mainUIBox), headerBar);
    gtk_box_append(GTK_BOX(mainUIBox), listBox);
    gtk_box_append(GTK_BOX(mainUIBox), createPasswordButton);
    gtk_window_set_child(GTK_WINDOW(window), mainUIBox);
    gtk_window_present(GTK_WINDOW(window));
}

int main(int argc, char **argv){
    GtkApplication* app;
    int status;
    app = gtk_application_new("org.password-manager.password-manager", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);
    return status;
}