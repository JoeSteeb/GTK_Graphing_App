#ifndef GRAPH_H
#define GRAPH_H

#include <gtk/gtk.h>
#include <string>
#include <iostream>
#include <list>
#include <vector>
#include <stdlib.h>
#include <ctgmath>
#include <memory>
#include "parseInterface.hpp"


typedef std::unique_ptr<int[]> point;

namespace Graph
{
    int Red[3] = {255,0,0};
    int Blue[3] = {0,0,255};
    int Green[3] = {0,255,0};

    struct Graph_View
    {
        GtkWidget *drawing_area;
        std::vector<GtkWidget *> equations;
        int transform[2];
        int zoom;
    };

    static void trigger_draw(GtkWidget *widget, gpointer data)
    {
        Graph_View *graph = (Graph_View *)data;
        gtk_widget_queue_draw(graph->drawing_area);
    }

    static void draw_line(cairo_t *cr, point start, point end, int color[3])
    {
        cairo_set_line_width(cr,2);
        cairo_set_source_rgb(cr, color[0], color[1], color[2]);
        cairo_move_to(cr, start[0], start[1]);
        cairo_line_to(cr, end[0], end[1]);
        cairo_stroke(cr);
    }

    static void draw_axis(cairo_t *cr, const Graph_View *graph, int width, int height)
    {
        // y-axis
        draw_line(
            cr,
            point(new int[2]{graph->transform[0],0}), 
            point(new int[2]{graph->transform[0], height}),
            Blue
        );        
        // x-axis
        draw_line(
            cr,
            point(new int[2]{0, graph->transform[1]}),  
            point(new int[2]{width, graph->transform[1]}), 
            Blue
        );
        int hash_width = graph->zoom/5;
        for(int i = graph->zoom; i < height; i+=graph->zoom)
        {
            // y-axis hash marks.
            draw_line(
                cr,
                point(new int[2]{graph->transform[0] - (hash_width),i}), 
                point(new int[2]{graph->transform[0] + (hash_width), i}),
                Blue
            );
        }
        for(int i = graph->transform[0]; i < width; i+=graph->zoom)
        {
            // x-axis hash marks.
            draw_line(
                cr,
                point(new int[2]{i, graph->transform[1] - (hash_width)}),  
                point(new int[2]{i, graph->transform[1] + (hash_width)}), 
                Blue
            );
        }
        for(int i = graph->transform[0]; i > 0; i-=graph->zoom)
        {
            // x-axis hash marks.
            draw_line(
                cr,
                point(new int[2]{i, graph->transform[1] - (hash_width)}),  
                point(new int[2]{i, graph->transform[1] + (hash_width)}), 
                Blue
            );
        }
        

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
        Graph_View *g,
        int equation_index,
        int width, 
        int height,
        int scale)
    {
        equation *e;
        std::vector<int> points;
        // std::cout << "graphing: " << g->Equation;
        const char *temp = gtk_editable_get_text(GTK_EDITABLE(g->equations[equation_index]));
        if(!strcmp(temp, ""))
            return points;
        char * eq = (char*)malloc(strlen(temp)*sizeof(char));
        strcpy(eq, temp);
        std::cout << "equation: {" << eq << "}\n";
        e = new equation(eq);
        std::cout << "equation evaluated for 1: {" << e->evaluate(1.00) << "}\n";
        char s[] = "x";
        for(float i = (float)(0.0 - g->transform[0])/scale; i < (float)(width - g->transform[0])/scale; i+=(1.00/scale))
        {
            std::cout << "x = " << i << " y = " << (e->evaluate(i)*scale) << "\n";
            points.push_back(height-(round(e->evaluate(i)*scale)+g->transform[1]));
        }
        return points;
    }

    static void draw_function(GtkDrawingArea *area,
        cairo_t *cr,
        int width,
        int height,
        gpointer data)
    {
        Graph_View *graph = (Graph_View *)data;        
        draw_axis(
            cr, 
            graph,
            width, 
            height
        );
        for(int i = 0; i < graph->equations.size(); i++)
        {
            draw_graph(cr, calculate_points(graph,i, width, height, 50), Red);
        }
        
        GdkRGBA color;
        GtkStyleContext *context;
        context = gtk_widget_get_style_context(GTK_WIDGET(area));
        gtk_style_context_get_color(context, &color);
        gdk_cairo_set_source_rgba(cr, &color);

        cairo_fill(cr);
    }

    void Build_Graph(Graph_View *graph)
    {
        if (!gtk_is_initialized())
        {
            gtk_init();
        }
        graph->zoom=50;
        graph->drawing_area = gtk_drawing_area_new();
        gtk_drawing_area_set_draw_func(GTK_DRAWING_AREA(graph->drawing_area),
                                       draw_function,
                                       (void *)graph, NULL);
    }

}

#endif