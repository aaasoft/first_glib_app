#include <glib.h>
#include <gio/gio.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    g_type_init();

    GError *error = NULL;

    GSocketClient * client = g_socket_client_new();

    GSocketConnection * connection = g_socket_client_connect_to_host (client,"localhost",4000,NULL,&error);


    if (error)
    {
        g_error(error->message);
    }
    else
    {
        g_message("Connection ok");
    }

    guint8 incoming_buff[100]= {0};

    GInputStream * in_stream = g_io_stream_get_input_stream(G_IO_STREAM(connection));
    GOutputStream * out_stream = g_io_stream_get_output_stream(G_IO_STREAM(connection));
    g_output_stream_write(out_stream, "Hello glib.\0", 12, NULL, &error);
    int incoming_num = g_input_stream_read(in_stream,incoming_buff,100,NULL,&error);

    if(error)
        g_error(error->message);
    else
    {
        int i=0;
        printf("incoming:\n");
        for(; i<incoming_num; i++)
            printf("%hhX ",incoming_buff[i]);
        printf("\n");

        //g_message(incoming_buff);
    }

    return TRUE;

}
