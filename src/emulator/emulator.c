#include <emulation/CPU/Z80.h>
#include <gtk/gtk.h>
#include <gdk/gdk.h>
#include <string.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

static const size_t s_c_height = 100;
static const size_t s_c_width  = 150;

GdkPixbuf* p_pix_buf = 0;

//GdkPixbuf *gdk_pixbuf_new(GdkColorspace colorspace,
//    gboolean has_alpha, int bits_per_sample,
//    int width, int height);

int main(int argc, char** argv)
{
    gtk_init(&argc, &argv);
    GtkWidget* p_shell = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    p_pix_buf = gdk_pixbuf_new(GDK_COLORSPACE_RGB, FALSE, 32, s_c_height, s_c_width);
    
    gtk_window_set_title(GTK_WINDOW(p_shell), "Z80 Emulator");
    gtk_window_set_default_size(GTK_WINDOW(p_shell), s_c_height, s_c_width);
    gtk_window_set_resizable(GTK_WINDOW(p_shell), FALSE);

    g_signal_connect(G_OBJECT(p_shell), "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_widget_show(GTK_WIDGET(p_shell));
    gtk_main();
    return 0;
}

//static uint8_t continuing;
//
//static const size_t s_c_memory_size = 0x1000;
//
//static char* instruction_names[256] = {
///*    0            1         2          3           4        5      6           7     8          9         A          B         C          D         E        F */
///* 0 */ "nop", "ld_SS_WORD" , "ld_vbc_a" , "inc_SS", "V_X", "V_X", "ld_X_BYTE", "rlca","ex_af_af_", "add_hl_SS", "ld_a_vbc", "dec_SS","V_X", "V_X","ld_X_BYTE", "rrca",
///* 1 */ "djnz_OFFSET", "ld_SS_WORD", "ld_vde_a", "inc_SS", "V_X", "V_X", "ld_X_BYTE", "rla","jr_OFFSET", "add_hl_SS", "ld_a_vde", "dec_SS","V_X", "V_X","ld_X_BYTE", "rra",
///* 2 */ "jr_Z_OFFSET", "ld_SS_WORD", "ld_vWORD_hl", "inc_SS", "V_X", "V_X", "ld_X_BYTE", "daa","jr_Z_OFFSET", "add_hl_SS", "ld_hl_vWORD", "dec_SS","V_X", "V_X","ld_X_BYTE", "cpl",
///* 3 */ "jr_Z_OFFSET", "ld_SS_WORD", "ld_vWORD_a", "inc_SS", "V_vhl", "V_vhl", "ld_vhl_BYTE", "scf","jr_Z_OFFSET", "add_hl_SS", "ld_a_vWORD", "dec_SS","V_X", "V_X","ld_X_BYTE", "ccf",
///* 4 */ "ld_X_Y", "ld_X_Y","ld_X_Y", "ld_X_Y", "ld_X_Y", "ld_X_Y", "ld_X_vhl", "ld_X_Y","ld_X_Y", "ld_X_Y","ld_X_Y", "ld_X_Y","ld_X_Y", "ld_X_Y","ld_X_vhl", "ld_X_Y",
///* 5 */ "ld_X_Y", "ld_X_Y","ld_X_Y", "ld_X_Y", "ld_X_Y", "ld_X_Y", "ld_X_vhl", "ld_X_Y","ld_X_Y", "ld_X_Y","ld_X_Y", "ld_X_Y","ld_X_Y", "ld_X_Y","ld_X_vhl", "ld_X_Y",
///* 6 */ "ld_X_Y", "ld_X_Y","ld_X_Y", "ld_X_Y", "ld_X_Y", "ld_X_Y", "ld_X_vhl", "ld_X_Y","ld_X_Y", "ld_X_Y","ld_X_Y", "ld_X_Y","ld_X_Y", "ld_X_Y","ld_X_vhl", "ld_X_Y",
///* 7 */ "ld_vhl_Y", "ld_vhl_Y","ld_vhl_Y", "ld_vhl_Y", "ld_vhl_Y", "ld_vhl_Y", "halt", "ld_vhl_Y", "ld_X_Y", "ld_X_Y","ld_X_Y", "ld_X_Y","ld_X_Y", "ld_X_Y","ld_X_vhl", "ld_X_Y",
///* 8 */ "U_a_Y", "U_a_Y","U_a_Y", "U_a_Y", "U_a_Y", "U_a_Y", "U_a_vhl","U_a_Y","U_a_Y", "U_a_Y","U_a_Y", "U_a_Y","U_a_Y", "U_a_Y","U_a_vhl", "U_a_Y",
///* 9 */ "U_a_Y", "U_a_Y","U_a_Y", "U_a_Y", "U_a_Y", "U_a_Y", "U_a_vhl","U_a_Y","U_a_Y", "U_a_Y","U_a_Y", "U_a_Y","U_a_Y", "U_a_Y","U_a_vhl", "U_a_Y",
///* A */ "U_a_Y", "U_a_Y","U_a_Y", "U_a_Y", "U_a_Y", "U_a_Y", "U_a_vhl","U_a_Y","U_a_Y", "U_a_Y","U_a_Y", "U_a_Y","U_a_Y", "U_a_Y","U_a_vhl", "U_a_Y",
///* B */ "U_a_Y", "U_a_Y","U_a_Y", "U_a_Y", "U_a_Y", "U_a_Y", "U_a_vhl","U_a_Y","U_a_Y", "U_a_Y","U_a_Y", "U_a_Y","U_a_Y", "U_a_Y","U_a_vhl", "U_a_Y",
///* C */ "ret_Z", "pop_TT","jp_Z_WORD", "jp_WORD", "call_Z_WORD", "push_TT", "U_a_BYTE", "rst_N","ret_Z", "ret","jp_Z_WORD", "CB","call_Z_WORD", "call_WORD", "U_a_BYTE", "rst_N",
///* D */ "ret_Z", "pop_TT","jp_Z_WORD", "out_vBYTE_a", "call_Z_WORD", "push_TT", "U_a_BYTE", "rst_N","ret_Z", "exx","jp_Z_WORD", "in_a_BYTE", "call_Z_WORD", "DD","U_a_BYTE", "rst_N",
///* E */ "ret_Z", "pop_TT","jp_Z_WORD", "ex_vsp_hl", "call_Z_WORD", "push_TT", "U_a_BYTE", "rst_N","ret_Z", "jp_hl","jp_Z_WORD", "ex_de_hl","call_Z_WORD", "ED","U_a_BYTE", "rst_N",
///* F */ "ret_Z", "pop_TT","jp_Z_WORD", "di", "call_Z_WORD", "push_TT", "U_a_BYTE", "rst_N","ret_Z", "ld_sp_hl","jp_Z_WORD", "ei","call_Z_WORD", "FD","U_a_BYTE", "rst_N"
//};
//
//uint8_t instructions [s_c_memory_size];
//
//static const size_t s_c_stack_top = 0xffff;
//static const size_t s_c_stack_size = 0x1000;
//uint8_t stack [s_c_stack_size];
//
//zuint8 in_cb(void *context, zuint16 port)
//{
//    printf("Value read from port: 0x%d: 0x0\n", port);
//    return 0x0;
//}
//
//void out_cb(void *context, zuint16 port, zuint8 value)
//{
//    printf("Value written to port: 0x%d: 0x%x\n", port, value);
//}
//
//void write_cb(void* context, zuint16 address, zuint8 value)
//{
//    if(((s_c_stack_top - s_c_stack_size) < address)
//     && (address <= s_c_stack_top))
//    {
//        printf("Value written: 0x%04x: 0x%x\n", address, value);
//        stack[s_c_stack_top - address] = value;
//    }
//    else if(address == 0x8000)
//    {
//        printf("Printed out: %c\n", value);
//    }
//}
//
//zuint8 read_cb(void* context, zuint16 address)
//{
//    zuint8 read_value = 0;
//    if(address < s_c_memory_size)
//    {
//        read_value = instructions[address];
//        printf( "Reading value: 0x%04x: 0x%02x (%s)\n"
//              , address
//              , read_value
//              , instruction_names[read_value]);
//    }
//    if(((s_c_stack_top - s_c_stack_size) < address)
//     && (address <= s_c_stack_top))
//    {
//        read_value = stack[s_c_stack_top - address];
//    }
//    return read_value;
//}
//
//void halt_cb(void* context, zboolean state)
//{
//    continuing = !state;
//}
//
//void read_binary(char* filename, uint8_t* instruct, size_t memory_size)
//{
//    int32_t fd = open(filename, O_RDONLY);
//    uint8_t continue_reading = TRUE;
//    memset(instruct, 0, memory_size);
//    while(continue_reading == TRUE)
//    {
//        ssize_t read_bytes = read(fd, instruct, memory_size);
//        printf("Read %ld bytes\n", read_bytes);
//        if(read_bytes <= 0)
//        {
//            continue_reading = FALSE;
//        }
//    }
//    close(fd);
//}
//
//int main(int argc, char** argv)
//{
//    continuing = TRUE;
//    
//    uint32_t iterations = 0;
//    
//    if(argc > 1)
//    {
//        read_binary(argv[1], instructions, s_c_memory_size);
//
//        Z80 z80;
//        z80.context = &z80;
//        z80.write = &write_cb;
//        z80.read = &read_cb;
//        z80.halt = &halt_cb;    
//        z80.in = &in_cb;
//        z80.out = &out_cb;
//
//        z80_power(&z80, TRUE);
//        z80_reset(&z80);
//        
//        while( (continuing == TRUE)
//            && (iterations++ < 0x2000))
//        {
//            z80_run(&z80, 1);
//        }
//    }
//    
//    return 0;
//}