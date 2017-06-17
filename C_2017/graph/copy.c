#include <gtk/gtk.h>

GdkPixbuf *create_pixbuf(const gchar * filename) {

 GdkPixbuf *pixbuf;
 GError *error = NULL;
 pixbuf = gdk_pixbuf_new_from_file(filename, &error);

 if (!pixbuf) {

  fprintf(stderr, "%s\n", error->message);
  g_error_free(error);
}

return pixbuf;
}

int main(int argc, char *argv[]) {

  GtkWidget *window;
  GdkPixbuf *icon;  
  GtkWidget *button;
  GtkWidget *halign;

  gtk_init(&argc, &argv);

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(window), "Icon");
  gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);


  gtk_container_set_border_width(GTK_CONTAINER(window), 15);
  button = gtk_button_new_with_label("Button");
  gtk_widget_set_tooltip_text(button, "Button widget");




  icon = create_pixbuf("dictionary.png");  
  gtk_window_set_icon(GTK_WINDOW(window), icon);
  
  gtk_widget_show(window);

  g_signal_connect(G_OBJECT(window), "destroy",
      G_CALLBACK(gtk_main_quit), NULL);

  g_object_unref(icon);    

  gtk_main();

  return 0;
}