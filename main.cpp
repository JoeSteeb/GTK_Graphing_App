#include <gtk/gtk.h>
#include <iostream>
#include <string>
#include "graph.hpp"
#include "./UI/equation_graph.hpp"


//TODO: Free this at some point lol
Graph::Graph_View *graph = new Graph::Graph_View;
int initial_width=900;
int initial_height=800;

// determines the fraction of the window occupide by graph.
float graph_vertical_fill = 1;
float graph_horizontal_fill = 0.65;

static void
activate(GtkApplication *app,
         gpointer user_data)
{
  // initializes static widgets.
  GtkWidget *window = gtk_application_window_new(app);
  GtkWidget *frame = gtk_frame_new(NULL);
  GtkWidget *superBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);;
  GtkWidget *equation_graph_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
  GtkWidget *equation_box_container;
  GtkWidget *add_equation = gtk_button_new_with_label("graph");;

  cairo_t *cr;

  // equation_graph_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
  equation_box_container = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

  gtk_window_set_title(GTK_WINDOW(window), "Window");
  gtk_window_set_default_size(GTK_WINDOW(window), initial_width, initial_height);

  gtk_widget_set_size_request(graph->drawing_area, (initial_width*graph_horizontal_fill), initial_height);
  gtk_frame_set_child(GTK_FRAME(frame), graph->drawing_area);
  gtk_window_set_child(GTK_WINDOW(window), superBox);

  ui::add_equation(equation_box_container, graph);
  ui::add_equation(equation_box_container, graph);
  gtk_box_append(GTK_BOX(equation_graph_box), equation_box_container);
  gtk_box_append(GTK_BOX(equation_graph_box), frame);
  gtk_box_append(GTK_BOX(superBox), equation_graph_box);

  
  gtk_widget_set_hexpand_set(equation_box_container, true);
  gtk_widget_set_hexpand(equation_box_container, false);

  gtk_widget_set_hexpand_set(frame, true);
  gtk_widget_set_hexpand(frame, true);


  gtk_window_present(GTK_WINDOW(window));
}

int main(int argc,
         char **argv)
{ 
  std::cout << (initial_width*graph_horizontal_fill)/2;
  graph->transform[0] = (initial_width*graph_horizontal_fill)/2; 
  graph->transform[1] = (initial_height/2);
  Graph::Build_Graph(graph);
  GtkApplication *app;
  int status;

  app = gtk_application_new("org.gtk.example", G_APPLICATION_FLAGS_NONE);
  g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
  status = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);

  return status;
}