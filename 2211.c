#include <vte/vte.h>

int main(int argc, char *argv[]) {
    GtkWidget *window, *t;

    gtk_init(&argc, &argv);
    t = vte_terminal_new();
    window   = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "2211");

    gchar **env = g_get_environ();
    gchar **cmd = (gchar *[]){g_strdup(g_environ_getenv(env, "SHELL")), NULL };
    g_strfreev(env);
    vte_terminal_fork_command_full(VTE_TERMINAL(t),
        VTE_PTY_DEFAULT, NULL, cmd, NULL, 0, NULL, FALSE, FALSE, FALSE);

    vte_terminal_set_scrollback_lines(VTE_TERMINAL(t), 0);
    vte_terminal_set_cursor_blink_mode(VTE_TERMINAL(t), VTE_CURSOR_BLINK_OFF);

    g_signal_connect(window,   "delete-event", gtk_main_quit, NULL);
    g_signal_connect(t, "child-exited", gtk_main_quit, NULL);
    gtk_container_add(GTK_CONTAINER(window), t);
    gtk_widget_show_all(window);
    gtk_main();
}
