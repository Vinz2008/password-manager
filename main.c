#include <stdlib.h>
#include <gtk/gtk.h>
#include <sodium.h>
#include "libs/csv.h"
#include "libs/encryption.h"

typedef struct {
char* name;
char* login;
char* password;
char* url;
} password_t;


typedef struct {
    password_t password;
} passwordwidget_t;

typedef struct {
    password_t* passwordList;
    size_t used;
    size_t size;
} PasswordList;


char* filename;
FILE* fpCsv;
GtkWidget *window;
GtkWidget* passwordDialogWindow;
PasswordList passwordListStruct;

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


void addPasswordToList(PasswordList* passwordlist, password_t password){
    if (passwordlist->used == passwordlist->size){
        passwordlist->size *=2;
        passwordlist->passwordList = realloc(passwordlist->passwordList, passwordlist->size * sizeof(password_t));
    }
    passwordlist->passwordList[passwordlist->used++] = password;
}




static void add_password(char* name, char* login, char* password, char* url){
    password_t Password;
    Password.name = malloc(30 * sizeof(char));
    Password.name = name;
    Password.login = malloc(30 * sizeof(char));
    Password.login = login;
    Password.password = malloc(30 * sizeof(char));
    Password.password = password;
    Password.url = malloc(30 * sizeof(char));
    Password.url = url;
    addPasswordToList(&passwordListStruct, Password);
}

static void add_password_dialog(GtkWidget *widget, gpointer data){
    passwordDialogWindow  = gtk_window_new();
    gtk_window_set_title(GTK_WINDOW(passwordDialogWindow), "dialog");
    gtk_window_set_default_size(GTK_WINDOW(passwordDialogWindow),355,200);
    GtkWidget* passwordDialogBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 9);
    GtkWidget* nameLabel = gtk_label_new("Name");
    GtkWidget* nameInput = gtk_text_new();
    gtk_widget_set_margin_start(nameInput, 5);
    GtkWidget* loginLabel = gtk_label_new("Login");
    GtkWidget* loginInput = gtk_text_new();
    gtk_widget_set_margin_start(loginInput, 5);
    GtkWidget* passwordLabel = gtk_label_new("Password");
    GtkWidget* passwordInput = gtk_text_new();
    gtk_widget_set_margin_start(passwordInput, 5);
    GtkWidget* urlLabel = gtk_label_new("Url");
    GtkWidget* urlInput = gtk_text_new();
    GtkWidget* addPasswordButton = gtk_button_new_with_label("Confirm");
    gtk_box_append(GTK_BOX(passwordDialogBox), nameLabel);
    gtk_box_append(GTK_BOX(passwordDialogBox), nameInput);
    gtk_box_append(GTK_BOX(passwordDialogBox), loginLabel);
    gtk_box_append(GTK_BOX(passwordDialogBox), loginInput);
    gtk_box_append(GTK_BOX(passwordDialogBox), passwordLabel);
    gtk_box_append(GTK_BOX(passwordDialogBox), passwordInput);
    gtk_box_append(GTK_BOX(passwordDialogBox), urlLabel);
    gtk_box_append(GTK_BOX(passwordDialogBox), urlInput);
    gtk_box_append(GTK_BOX(passwordDialogBox), addPasswordButton);
    gtk_window_set_child(GTK_WINDOW(passwordDialogWindow), passwordDialogBox);
    gtk_window_present(GTK_WINDOW(passwordDialogWindow));
}


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

void create_password_widget(GtkWidget* Box, password_t* password){
    GtkWidget* PasswordName = gtk_label_new(password->name);
    /*GtkWidget* boxPassword = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    gtk_box_append(GTK_BOX(Box), boxPassword);*/
    gtk_box_append(GTK_BOX(Box), PasswordName);
}

void create_list_password_widget(GtkWidget* Box){
    
}


static void activate(GtkApplication *app, gpointer data){
    window = gtk_application_window_new(app);
    //GtkWidget* headerBar = gtk_header_bar_new();
    /*GtkListItemFactory *factory = gtk_signal_list_item_factory_new();
    g_signal_connect(factory, "setup", setup_listitem, NULL);
    g_signal_connect(factory, "bind", bind_listitem, NULL);*/
    GtkWidget* listPasswordBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 1);
    create_list_password_widget(listPasswordBox);
    GtkWidget* separator_list_button = gtk_separator_new(GTK_ORIENTATION_HORIZONTAL);
    GtkWidget* createPasswordButton = gtk_button_new_with_label("Create Password");
    g_signal_connect(createPasswordButton, "clicked", G_CALLBACK(add_password_dialog), NULL);
    GtkWidget *mainUIBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 3);
    //GtkWidget* listView = gtk_list_view_new();
    //gtk_box_append(GTK_BOX(mainUIBox), headerBar);
    //gtk_box_append(GTK_BOX(mainUIBox), listView);
    gtk_box_append(GTK_BOX(mainUIBox), listPasswordBox);
    gtk_box_append(GTK_BOX(mainUIBox), separator_list_button);
    gtk_box_append(GTK_BOX(mainUIBox), createPasswordButton);
    gtk_window_set_child(GTK_WINDOW(window), mainUIBox);
    gtk_window_present(GTK_WINDOW(window));
}

int main(int argc, char **argv){
    passwordListStruct.passwordList = malloc(100 * sizeof(password_t));
    passwordListStruct.used = 0;
    passwordListStruct.size = 1;
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