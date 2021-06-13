/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  13/06/2021 15:59:28
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <gtk/gtk.h>
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

typedef struct {
    GtkWidget *w_dlg_file_choose;       // Pointer to file chooser dialog box
    GtkWidget *w_img_main;              // Pointer to image widget
    GtkWidget *w_encrypt_dialog_msg; 
    GtkWidget *w_text_to_encrypt;
} app_widgets;


int main(int argc, char *argv[])
{
    GtkBuilder      *builder;
    GtkWidget       *window;
    app_widgets     *widgets = g_slice_new(app_widgets);

    gtk_init(&argc, &argv);

    builder = gtk_builder_new_from_file("glade/window_main.glade");

    window = GTK_WIDGET(gtk_builder_get_object(builder, "window_main"));
    widgets->w_dlg_file_choose = GTK_WIDGET(gtk_builder_get_object(builder, "dlg_file_choose"));
    widgets->w_img_main = GTK_WIDGET(gtk_builder_get_object(builder, "img_main")); 
    widgets->w_encrypt_dialog_msg = GTK_WIDGET(gtk_builder_get_object(builder, "encrypt_dialog_msg")); 
    widgets->w_text_to_encrypt = GTK_WIDGET(gtk_builder_get_object(builder, "text_to_encrypt"));
    
    gtk_builder_connect_signals(builder, widgets);

    g_object_unref(builder);

    gtk_widget_show(window);                
    gtk_main();
    g_slice_free(app_widgets, widgets);

    return 0;
}


// File --> Open
void on_menuitm_open_activate(GtkMenuItem *menuitem, app_widgets *app_wdgts)
{
	gchar *file_name = NULL;        // Name of file to open from dialog box

	// Show the "Open Image" dialog box
	gtk_widget_show(app_wdgts->w_dlg_file_choose);

	// Check return value from Open Image dialog box to see if user clicked the Open button
	if (gtk_dialog_run(GTK_DIALOG (app_wdgts->w_dlg_file_choose)) == GTK_RESPONSE_OK) {
		// Get the file name from the dialog box

		file_name = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(app_wdgts->w_dlg_file_choose));
		if (file_name != NULL) {
			int pid = fork();
			if(pid == 0)
			{
				gchar *args[3] = {"./decode/decode", file_name, NULL};
				execvp(args[0], args);}
			else
				gtk_image_set_from_file(GTK_IMAGE(app_wdgts->w_img_main), file_name);
		}
		g_free(file_name);
	}
	

	gtk_widget_hide(app_wdgts->w_dlg_file_choose);
}

// File --> Quit
void on_menuitm_close_activate(GtkMenuItem *menuitem, app_widgets *app_wdgts)
{
    gtk_main_quit();
}

// called when window is closed
void on_window_main_destroy()
{
    gtk_main_quit();
}

void enter_callback_2( GtkWidget *widget, GtkWidget *entry, GtkWidget *widge )
{
	const gchar *entry_text;
	entry_text = gtk_entry_get_text (GTK_ENTRY (entry));
	printf ("Entry contents: %s\n", entry_text);
	int pid = fork();
	if(pid == 0)
	{
		//./qrcode --output:bmp --bmp-scale 8 --file hello.bmp "Hello, World!"

		gchar *args[8] = {"./encode/encode","--output:bmp","--bmp-scale", "8", "--file", "output/results.bmp", entry_text ,  NULL};
		execvp(args[0], args);
	}
	else
	{
		sleep(2);
		gtk_image_set_from_file(GTK_IMAGE(widge), "output/results.bmp");
	}
}

void on_btn_encrypt_message_activate(GtkMessageDialog *encrypt_dialog_msg, app_widgets *app_wdgts)
{
	gtk_widget_show(app_wdgts->w_encrypt_dialog_msg);
	if (gtk_dialog_run(GTK_DIALOG (app_wdgts->w_encrypt_dialog_msg)) == GTK_RESPONSE_OK) 
	{
		enter_callback_2(app_wdgts->w_encrypt_dialog_msg, app_wdgts->w_text_to_encrypt, app_wdgts->w_img_main);
	}

	gtk_widget_hide(app_wdgts->w_encrypt_dialog_msg);

}


