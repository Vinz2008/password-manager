#include <stdlib.h>
#include <gtk/gtk.h>
#include <sodium.h>
#include "libs/csv.h"
#include "libs/encryption.h"

char* filename;
FILE* fpCsv;
GtkWidget *window;


static void open_file(char* filename){
    fpCsv = fopen(filename,"r+");
    char** lineDescriptor;
    lineDescriptor = malloc(1000 * sizeof(char*));
    getLineCSV(lineDescriptor, fpCsv);
}


static void on_response_file_chooser(GtkDialog *dialog,int response){
    if (response == GTK_RESPONSE_ACCEPT){
      GtkFileChooser *chooser = GTK_FILE_CHOOSER(dialog);
      g_autoptr(GFile) file = gtk_file_chooser_get_file(chooser); // TODO: change to use gtk_file_chooser_get_files()
      filename = g_file_get_path(file);
      open_file(filename);
    }
    gtk_window_destroy(GTK_WINDOW(dialog));
}



static void open_file_dialog(GtkApplication *app, gpointer data){
    GtkWidget *dialog;
    GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;
    dialog = gtk_file_chooser_dialog_new("Open File",GTK_WINDOW(window),action, ("_Cancel"),GTK_RESPONSE_CANCEL, ("_Open"),GTK_RESPONSE_ACCEPT,NULL);
    gtk_widget_show(dialog);
    g_signal_connect(dialog, "response", G_CALLBACK(on_response_file_chooser),NULL);
}


typedef struct {
char* name;
char* login;
char* password;
char* url;
} password_t;


char* password_get_string(password_t* obj){
    obj->name ="test";
    return obj->name;

}

static void setup_listitem(GtkListItemFactory *factory, GtkListItem *list_item){
    GtkWidget *label = gtk_label_new("");
    gtk_list_item_set_child(list_item, label);
}


static void bind_listitem (GtkListItemFactory *factory, GtkListItem *list_item){
  GtkWidget *label;
  password_t *obj;
  label = gtk_list_item_get_child(list_item);
  obj = gtk_list_item_get_item(list_item);
  gtk_label_set_label(GTK_LABEL (label),password_get_string(obj));
}



GtkWidget* create_widget_func(GObject* item, gpointer user_data){
    
}


GDestroyNotify freeListPassword(){

}


static void activate(GtkApplication *app, gpointer data){
    window = gtk_application_window_new(app);
    //GtkWidget* headerBar = gtk_header_bar_new();
    /*GtkListItemFactory *factory = gtk_signal_list_item_factory_new();
    g_signal_connect(factory, "setup", setup_listitem, NULL);
    g_signal_connect(factory, "bind", bind_listitem, NULL);*/
    GListModel* model;
    GtkWidget* listboxPasswords = gtk_list_box_new();
    gtk_list_box_bind_model(GTK_LIST_BOX(listboxPasswords), model, create_widget_func, NULL, freeListPassword);
    GtkWidget* separator_list_button = gtk_separator_new(GTK_ORIENTATION_HORIZONTAL);
    GtkWidget* createPasswordButton = gtk_button_new_with_label("Create Password");
    g_signal_connect(createPasswordButton, "clicked", G_CALLBACK(open_file_dialog), NULL);
    GtkWidget *mainUIBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 3);
    //GtkWidget* listView = gtk_list_view_new();
    //gtk_box_append(GTK_BOX(mainUIBox), headerBar);
    //gtk_box_append(GTK_BOX(mainUIBox), listView);
    gtk_box_append(GTK_BOX(mainUIBox), separator_list_button);
    gtk_box_append(GTK_BOX(mainUIBox), createPasswordButton);
    gtk_window_set_child(GTK_WINDOW(window), mainUIBox);
    gtk_window_present(GTK_WINDOW(window));
}

int main(int argc, char **argv){
    if (sodium_init() < 0){
        printf("Couldn't initialize libsodium");
        exit(1);
    }
    char hash[crypto_pwhash_STRBYTES];
    create_hash_from_password("test", hash);
    printf("hash : %s\n", hash);
    char encrypted_str[1000];
    //encrypt_str("hello", encrypt_str, hash, 0);
    FILE* fptr;
    fptr = fopen("test.csv", "r");
    char** line;
    line = malloc(100 * sizeof(char*));
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