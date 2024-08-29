#include<iostream>
#include<string>
#include<stdlib.h>
#include<gtk/gtk.h>
#include <X11/Xlib.h>

Display* d = XOpenDisplay(NULL);
Screen*  s = DefaultScreenOfDisplay(d);

GtkWidget *label;
GtkWidget *frame_rate;
GtkWidget *file_name;
GtkWidget *start_button;
GtkWidget *window;
GtkWidget *box;

static void record(GtkWidget *button, gpointer *data) {
    int height = s->height;
    int width = s->width;
    std::string s = std::to_string(height) + "x" + std::to_string(width);
    std::string rate = gtk_entry_get_text(GTK_ENTRY(frame_rate));
    std::string name = gtk_entry_get_text(GTK_ENTRY(file_name));
    std::string fin = "ffmpeg -f x11grab -framerate " + rate + " -video_size cif -i :0.0 " + name;
    system(fin.c_str());
}

int main(int argc, char * argv[]) {
  gtk_init(&argc, &argv);

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  frame_rate = gtk_entry_new();
  file_name = gtk_entry_new();
  start_button = gtk_button_new_with_label("record");

  g_signal_connect(start_button, "clicked", G_CALLBACK(record), NULL);

  gtk_container_add(GTK_CONTAINER(window), box);
  gtk_container_add(GTK_CONTAINER(box), frame_rate);
  gtk_container_add(GTK_CONTAINER(box), file_name);
  gtk_container_add(GTK_CONTAINER(box), start_button);

  gtk_widget_show_all(window);

  gtk_main();

  // system("ffmpeg -video_size 1024x768 -framerate 60 -f x11grab -i :0.0+100,200 output.mp4");
  return 0;
}
