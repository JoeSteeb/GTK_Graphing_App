#ifndef EQUATION_GRAPH_H
#define EQUATION_GRAPH_H
#include <gtk/gtk.h>
#include "../graph.hpp"
namespace ui
{

    void add_to_box(GtkWidget *container, GtkWidget *widget)
    {        
        gtk_box_append(GTK_BOX(container), widget);
    }    

    void add_equation(GtkWidget *container, Graph::Graph_View *graph)
    {
        GtkWidget *equation_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
        GtkWidget *user_input = gtk_entry_new();
        GtkWidget *button = gtk_button_new_with_label("graph");
        gtk_widget_set_valign(equation_box, GTK_ALIGN_START);
        gtk_widget_set_vexpand(equation_box, false);
        gtk_widget_set_vexpand_set(equation_box, true);
        gtk_widget_set_hexpand(equation_box, true);
        gtk_widget_set_hexpand_set(equation_box, true);
        add_to_box(equation_box, user_input);
        add_to_box(equation_box, button);
        add_to_box(container, equation_box);

        graph->equations.push_back(user_input);

        g_signal_connect(button, "clicked", G_CALLBACK(Graph::trigger_draw), (void *)graph);
    }
}

#endif