#include <gtk/gtk.h>

// Structure to hold application state data
typedef struct {
    int count;
    GtkWidget *label;
} AppData;

// Callback function executed when the button is clicked
static void on_button_clicked(GtkWidget *widget, gpointer data) {
    AppData *app = (AppData *) data;
    app->count++;
    
    char buffer[64];
    snprintf(buffer, sizeof(buffer), "Clicks: %d", app->count);
    gtk_label_set_text(GTK_LABEL(app->label), buffer);
}

static void activate(GtkApplication *app, gpointer user_data) {
    // Allocate state container
    AppData *app_data = g_new0(AppData, 1);
    app_data->count = 0;

    // Create the main window
    GtkWidget *window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Button Clicker");
    gtk_window_set_default_size(GTK_WINDOW(window), 320, 200);

    // Create a layout grid centered in the window
    GtkWidget *grid = gtk_grid_new();
    gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(grid, GTK_ALIGN_CENTER);
    gtk_grid_set_row_spacing(GTK_GRID(grid), 15);
    gtk_container_add(GTK_CONTAINER(window), grid);

    // Create the counter display label
    app_data->label = gtk_label_new("Clicks: 0");
    gtk_grid_attach(GTK_GRID(grid), app_data->label, 0, 0, 1, 1);

    // Create the clickable button
    GtkWidget *button = gtk_button_new_with_label("Click");
    g_signal_connect(button, "clicked", G_CALLBACK(on_button_clicked), app_data);
    gtk_grid_attach(GTK_GRID(grid), button, 0, 1, 1, 1);

    // Free memory automatically when the window is destroyed
    g_signal_connect_swapped(window, "destroy", G_CALLBACK(g_free), app_data);

    gtk_widget_show_all(window);
}

int main(int argc, char **argv) {
    GtkApplication *app = gtk_application_new("org.example.clicker", G_APPLICATION_DEFAULT_FLAGS);
    
    
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    
    int status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);
    return status;
}
