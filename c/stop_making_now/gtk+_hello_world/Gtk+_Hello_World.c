#include <gtk/gtk.h>

//ボタンがクリックされたときに呼び出される関数
static void button_clicked(GtkWidget *button, gpointer user_data)
{
  gtk_main_quit();
}
 
int main(int argc, char** argv){
  GtkWidget *window;
 
  //gtkを初期化する。おまじない。
  gtk_init(&argc,&argv);
 
  //ウインドウウィジェットを作成する。
  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
 
  //ウインドウの大きさを指定
  gtk_window_set_title(GTK_WINDOW(window), "Hello");
  gtk_widget_set_size_request(window,300,200);
  {//パッキンボックスを作る
    GtkWidget *vbox;
    vbox = gtk_vbox_new(FALSE, 2);
 
    //パッキンボックスをwindowに乗っける
    gtk_container_add(GTK_CONTAINER(window), vbox);
    {
/*      GtkWidget *image;
      GtkWidget *button;*/
      GtkWidget *label;
 
/*      //画像を読み込むためのウィジェットを作成し，
      //vboxの上半分に乗っける。
      image = gtk_image_new_from_file("girl.png");
      gtk_box_pack_start(GTK_BOX(vbox), image, TRUE, TRUE, 0);
 
      //ボタンはvboxの下半分に乗っける。
      button = gtk_button_new_with_label("Quit");
      gtk_box_pack_start(GTK_BOX(vbox), button, FALSE, FALSE, 0);
      g_signal_connect (G_OBJECT(button), "clicked" ,
            G_CALLBACK(button_clicked), NULL);*/
      //ボタンはvboxの下半分に乗っける。
      label = gtk_button_new_with_label("hello world!!");
      gtk_box_pack_start(GTK_BOX(vbox), label, FALSE, FALSE, 0);

    }
  }
 
  //ウインドウを閉じるときにプログラムも終了する。
  g_signal_connect(window, "destroy",
      G_CALLBACK(gtk_main_quit), NULL);

   //windowの上にある物も全て表示する。(_allが付くことに注意)
  gtk_widget_show_all(window);
 
  gtk_main();
 
  return 0;
}