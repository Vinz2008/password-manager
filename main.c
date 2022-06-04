#include <stdlib.h>
#include <gtk/gtk.h>
#include <sodium.h>
#include "libs/csv.h"

FILE* fpCsv;


static void open_file_dialog(){

}

void open_file(){

}


typedef struct {
char* name;
} password_t;



char* password_get_string(password_t* obj){
    obj->name ="test";
    return obj->name;

}

static void setup_listitem(GtkListItemFactory *factory, GtkListItem *list_item){
    GtkWidget *label = gtk_label_new ("");
    gtk_list_item_set_child (list_item, label);
}


static void bind_listitem (GtkListItemFactory *factory, GtkListItem *list_item){
  GtkWidget *label;
  password_t *obj;
  label = gtk_list_item_get_child(list_item);
  obj = gtk_list_item_get_item(list_item);
  gtk_label_set_label(GTK_LABEL (label),password_get_string(obj));
}


static void activate(GtkApplication *app, gpointer data){
    GtkWidget *window = gtk_application_window_new(app);
    //GtkWidget* headerBar = gtk_header_bar_new();
    /*GtkListItemFactory *factory = gtk_signal_list_item_factory_new();
    g_signal_connect(factory, "setup", setup_listitem, NULL);
    g_signal_connect(factory, "bind", bind_listitem, NULL);*/
    GtkWidget *createPasswordButton = gtk_button_new_with_label("Create Password");
    GtkWidget *mainUIBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 3);
    //GtkWidget* listView = gtk_list_view_new();
    //gtk_box_append(GTK_BOX(mainUIBox), headerBar);
    //gtk_box_append(GTK_BOX(mainUIBox), listView);
    gtk_box_append(GTK_BOX(mainUIBox), createPasswordButton);
    gtk_window_set_child(GTK_WINDOW(window), mainUIBox);
    gtk_window_present(GTK_WINDOW(window));
}

int main(int argc, char **argv){
    FILE* fptr;
    fptr = fopen("test.csv", "r");
    char line[1000][1000];
    getLineCSV(line, fptr);
    for (int i = 0; i < 4; i++){
        printf("line[%d] : %s\n", i, line[i]);
    }
    fclose(fptr);
    printf("test\n");
    GtkApplication* app;
    int status;
    app = gtk_application_new("org.password-manager.password-manager", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);
    return status;
}