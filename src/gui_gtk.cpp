#include <gtk/gtk.h>
#include "linux_display_manager.h"  // Linux-specific header for resolution handling
#include <vector>
#include <iostream>

// Function to update the resolution display list in GTK GUI
void updateResolutionList(GtkComboBox* combo_box) {
    std::vector<ScreenResolution> resolutions = getLinuxResolutions();

    for (const auto& res : resolutions) {
        std::string resolution_str = std::to_string(res.width) + "x" + std::to_string(res.height);
        gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo_box), resolution_str.c_str());
    }
}

// Function to handle resolution selection
void onResolutionSelected(GtkComboBox* combo_box, gpointer user_data) {
    // Get the selected resolution
    gchar* selected_resolution = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(combo_box));
    
    if (selected_resolution) {
        int width = std::stoi(selected_resolution);  // Example parsing, modify if necessary
        int height = 1080; // For now, assume 1080p, you can improve resolution parsing here.
        setLinuxResolution(width, height);
        g_free(selected_resolution);
    }
}

// Main GTK setup function
int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    GtkWidget* window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "ResoManager");
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Create a combo box for selecting resolution
    GtkWidget* combo_box = gtk_combo_box_text_new();
    updateResolutionList(GTK_COMBO_BOX(combo_box));

    g_signal_connect(combo_box, "changed", G_CALLBACK(onResolutionSelected), NULL);
    
    GtkWidget* vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_box_pack_start(GTK_BOX(vbox), combo_box, TRUE, TRUE, 0);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}
