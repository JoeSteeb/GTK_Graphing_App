#ifndef EQUATION_GRAPH_H
#define EQUATION_GRAPH_H
#include <iostream>
#include <gtk/gtk.h>
#include <algorithm>
#include <numeric>
#include "../graph.hpp"
#include <vector>

namespace ui
{
    struct graphAndEquation
    {
        Graph::Graph_View *graph;
        GtkWidget *equation_box;
        GtkWidget *user_input;
    };

    void add_to_box(GtkWidget *container, GtkWidget *widget)
    {
        gtk_box_append(GTK_BOX(container), widget);
    }

    static void trigger_delete(GtkWidget *widget, gpointer data)
    {
        graphAndEquation *g = reinterpret_cast<graphAndEquation *>(data);

        std::cout << "\nAfter pass: " << g;

        // Remove the equation box from its parent container
        gtk_widget_unparent(g->equation_box);
        // Find the equation_box in the vector and remove it
        std::erase_if(g->graph->equations, [g](GtkWidget *equation)
                      { 
            if (equation == g->user_input){
                std::cout << "found equation";
            }else{
                std::cout << "equation not found";
            }
            std::cout << "\n";
            return equation == g->user_input; });
        delete g;
    }

    void add_equation(GtkWidget *container, Graph::Graph_View *graph)
    {
        GtkWidget *equation_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
        GtkWidget *user_input = gtk_entry_new();
        GtkWidget *graphButton = gtk_button_new_with_label("Graph");
        GtkWidget *deleteButton = gtk_button_new_with_label("Delete");
        gtk_widget_set_valign(equation_box, GTK_ALIGN_START);
        gtk_widget_set_vexpand(equation_box, false);
        gtk_widget_set_vexpand_set(equation_box, true);
        gtk_widget_set_hexpand(equation_box, true);
        gtk_widget_set_hexpand_set(equation_box, true);
        add_to_box(equation_box, user_input);
        add_to_box(equation_box, graphButton);
        add_to_box(equation_box, deleteButton);
        add_to_box(container, equation_box);

        graph->equations.push_back(user_input);

        g_signal_connect(graphButton, "clicked", G_CALLBACK(Graph::trigger_draw), (void *)graph);
        graphAndEquation *data = new graphAndEquation;
        data->graph = graph;
        data->equation_box = equation_box;
        data->user_input = user_input;
        std::cout << "before pass: " << &data;
        std::cout << "\n";
        g_signal_connect(deleteButton, "clicked", G_CALLBACK(trigger_delete), (void *)data);
    }
}

#endif