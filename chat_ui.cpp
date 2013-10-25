#include <FL/Fl.H>
#include <FL/Fl_Text_Display.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Return_Button.H>
#include <FL/Fl_Text_Editor.H>
#include <FL/Fl_Text_Buffer.H>

#include <communication.h>

Communication *comm = NULL;



void send_data(Fl_Widget*, void *txt_edtr)
{
    Fl_Text_Buffer *msg_out = (Fl_Text_Buffer*)txt_edtr;
   
    //printf("MSGL = %s\n", msg_out->text());
    if(msg_out->length() > 0)
    {
        comm->Send((char*)msg_out->text());
        msg_out->text("");
    }  
}

void *listen_data(void *data)
{
    char *msg;
    Fl_Text_Display *msg_dsp = (Fl_Text_Display *)data;
  
    while(1)
    {
      
        msg = comm->Listen();
        
        printf("MSGL = %s\n", msg);
        msg_dsp->insert(msg);
        msg_dsp->insert("\n");
        msg_dsp->redraw();
    } 
    
    //pthread_exit((void*) 0);
    
}


int main()
{
    //Fl::lock();
    Fl_Window *win = new Fl_Window(0, 0, 640, 480, "BChat");
    Fl_Text_Buffer  *dsp_buf  = new Fl_Text_Buffer;
    Fl_Text_Buffer  *msg_buf  = new Fl_Text_Buffer;
    Fl_Text_Editor  *msg_out  = new Fl_Text_Editor(10, 370, 530, 100);
    Fl_Text_Display *msg_dsp  = new Fl_Text_Display(10, 10, 620, 340);
    Fl_Button       *send_btn = new Fl_Button(550, 380, 80, 80, "Send");
    comm                      = new Communication(3310);
    
    msg_out->wrap_mode(Fl_Text_Editor::WRAP_AT_BOUNDS, 0);
    
    msg_out->buffer(dsp_buf);
    msg_dsp->buffer(msg_buf);
    
    pthread_t thread_listen;
    pthread_create(&thread_listen, NULL, listen_data, (void*)msg_dsp);
    
    send_btn->callback(send_data, (void*)dsp_buf);
    //msg_out->callbak(send_data, (void*)dsp_buf);
    //send_btn->when(FL_WHEN_ENTER_KEY);
    
    
    win->show();
    
    return Fl::run(); 
}
