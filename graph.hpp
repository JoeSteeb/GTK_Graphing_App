#ifndef GRAPH_H
#define GRAPH_H

#include <gtk/gtk.h>
#include <string>
#include <iostream>
#include <list>
#include <vector>
#include <stdlib.h>
#include <ctgmath>
#include "parseInterface.hpp"

namespace Graph
{
    int Red[3] = {255,0,0};
    int Blue[3] = {0,0,255};
    int Green[3] = {0,255,0};

    struct Graph
    {
        GtkWidget *drawing_area;
        std::string Equation;
        int transform[2];
        int zoom;
    };


    static void draw_line(cairo_t *cr, int start[2], int end[2], int color[3])
    {
        cairo_set_line_width(cr,2);
        cairo_set_source_rgb(cr, color[0], color[1], color[2]);
        cairo_move_to(cr, start[0], start[1]);
        cairo_line_to(cr, end[0], end[1]);
        cairo_stroke(cr);
    }

    static void draw_graph(cairo_t *cr, std::vector<int> points, int color[3])
    {
        int previous = 0;

        for(int i = 1; i < points.size(); i++) 
        {
            cairo_set_line_width(cr,2);
            cairo_set_source_rgb(cr, color[0], color[1], color[2]);
            cairo_move_to(cr, previous, points[previous]);
            cairo_line_to(cr, i,points[i]);
            cairo_stroke(cr);
            previous++;
           // std::cout << "from: " << "(" << previous << "," << points[previous] << ")\n";
           // std::cout << "to: " << "(" << i << "," << points[i] << ")\n";
        }
    }

    static std::vector<int> 
    calculate_points(
        Graph *g,
        int width, 
        int height,
        int scale)
    {
        equation *e;
        std::vector<int> points;
        std::cout << "graphing: " << g->Equation;
        const char *temp = g->Equation.c_str();
        char * eq = (char*)malloc(strlen(temp));
        strcpy(eq, temp);
        e = new equation(eq);
        for(float i = (float)(0.0 - g->transform[0])/scale; i < (float)(width - g->transform[0])/scale; i+=(1.00/scale))
        {
            std::cout << "x = " << i << " y = " << (e->evaluate(i)*scale) << "\n";
            points.push_back(height-(round(e->evaluate(i)*scale)+g->transform[1]));
        }
        return points;
    }

    static void
    draw_function(GtkDrawingArea *area,
        cairo_t *cr,
        int width,
        int height,
        gpointer data)
    {
        Graph *graph = (Graph *)data;
        calculate_points(
            graph,
            width, 
            height,
            1 
        );

        draw_graph(cr, calculate_points((Graph *)data, width, height, 50), Red);
        int xAxis1[2] = {graph->transform[0], 0};
        int xAxis2[2] = {graph->transform[0], height};
        int yAxis1[2] = {0, graph->transform[1]};
        int yAxis2[2] = {width, graph->transform[1]};
        
        draw_line(cr,xAxis1, xAxis2, Blue);
        draw_line(cr,yAxis1, yAxis2, Blue);

        GdkRGBA color;
        GtkStyleContext *context;
        context = gtk_widget_get_style_context(GTK_WIDGET(area));
        gtk_style_context_get_color(context, &color);
        gdk_cairo_set_source_rgba(cr, &color);

        cairo_fill(cr);
    }

    void Build_Graph(Graph *graph)
    {
        if (!gtk_is_initialized())
        {
            gtk_init();
        }
        graph->drawing_area = gtk_drawing_area_new();
        gtk_drawing_area_set_draw_func(GTK_DRAWING_AREA(graph->drawing_area),
                                       draw_function,
                                       (void *)graph, NULL);
    }

}

#endif