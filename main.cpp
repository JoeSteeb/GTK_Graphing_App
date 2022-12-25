#include <gtk/gtk.h>
#include "graph.hpp"
#include <iostream>
#include <string>


//TODO: Free this at some point lol
Graph::Graph *graph = new Graph::Graph;
int initial_width=600;
int initial_height=800;
GtkWidget *userInput;

static void
print_hello(GtkWidget *widget, gpointer data)
{
  // g_print("Hello World\n");
  // gtk_widget_set_size_request(graph->drawing_area, 800, 800);
  std::string input = gtk_editable_get_text(GTK_EDITABLE(userInput));
  if(input == "")
  {
    return;
  }
  graph->Equation = input;
  std::cout << "button pressed, input = " << graph->Equation << "\n";
  gtk_widget_queue_draw(graph->drawing_area);
}

static void
activate(GtkApplication *app,
         gpointer user_data)
{
  GtkWidget *window;
  GtkWidget *frame;
  GtkWidget *button;
  GtkWidget *superBox;
  GtkWidget *equationBox;

  cairo_t *cr;

  button = gtk_button_new_with_label("graph");
  userInput = gtk_entry_new();

  superBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  equationBox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);

  window = gtk_application_window_new(app);
  gtk_window_set_title(GTK_WINDOW(window), "Window");
  gtk_window_set_default_size(GTK_WINDOW(window), initial_width, initial_height);

  frame = gtk_frame_new(NULL);
  gtk_widget_set_size_request(graph->drawing_area, initial_width, initial_height);
  gtk_frame_set_child(GTK_FRAME(frame), graph->drawing_area);

  g_signal_connect(button, "clicked", G_CALLBACK(print_hello), NULL);
  gtk_window_set_child(GTK_WINDOW(window), superBox);

  gtk_box_append(GTK_BOX(equationBox), userInput);
  gtk_box_append(GTK_BOX(equationBox), button);
  gtk_box_append(GTK_BOX(superBox), equationBox);
  gtk_box_append(GTK_BOX(superBox), frame);

  gtk_window_present(GTK_WINDOW(window));
}

int main(int argc,
         char **argv)
{
  graph->Equation = "sin(x)";
  graph->transform[0] = initial_width/2; 
  graph->transform[1] = initial_height/2;
  Graph::Build_Graph(graph);
  GtkApplication *app;
  int status;

  app = gtk_application_new("org.gtk.example", G_APPLICATION_FLAGS_NONE);
  g_signal_connect(app, "activate", G_CALLBACK(activate), (void *)userInput);
  status = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);

  return status;
}