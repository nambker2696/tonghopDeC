void window_dialog(GtkWidget *widget,gpointer data){
	GtkBuilder *builder;
	GtkWidget *window;
	GtkWidget *word_tu;
	GtkWidget *mean_nghia;
	GtkWidget *thongbao;
	GtkWidget *tu;
	GtkWidget *nghia;
	char word[MAXLEN_WORD];
	char mean[MAXLEN_MEAN];
	int rsize;

	builder = gtk_builder_new();
	gtk_builder_add_from_file(builder, "library/data/giaodien.glade", NULL);
	window = GTK_WIDGET(gtk_builder_get_object(builder, "window_dialog"));
	gtk_window_set_title (GTK_WINDOW (window), "KQ ADD");
	word_tu = GTK_WIDGET(gtk_builder_get_object(builder, "tu"));
	mean_nghia = GTK_WIDGET(gtk_builder_get_object(builder, "nghia"));
	thongbao = GTK_WIDGET(gtk_builder_get_object(builder, "thongbao"));
	
	strcpy(word,(char*)gtk_entry_get_text(GTK_ENTRY(add_tu)));
	strcpy(mean,(char*)gtk_entry_get_text(GTK_ENTRY(add_nghia)));
	xoakhoangtrangcuoichuoi(word);
	if((strcmp(word,"")== 0) || (strcmp(mean,"")== 0)){
		gtk_label_set_text(GTK_LABEL(thongbao),"Thông báo:_______________________________\n\n        -Bạn chưa nhập đầy đủ dữ liệu.\n       -Dữ liệu nhập vào không được chứa toàn dấu cách.");
	}
	else{
		if(btsel(dic,word,mean,MAXLEN_MEAN*sizeof(char),&rsize)==0){
			gtk_label_set_text(GTK_LABEL(thongbao),"Thông báo:_________________________________\n\n        -Từ này đã tồn tại.");
		}
		else{
			if(btins(dic,word,mean,MAXLEN_MEAN*sizeof(char)))
				gtk_label_set_text(GTK_LABEL(thongbao),"Thông báo:________________________________\n\n        -Thêm từ không thành công - Tràn bộ nhớ");
			else
				gtk_label_set_text(GTK_LABEL(word_tu),word);
			gtk_label_set_text(GTK_LABEL(mean_nghia),nghia);
			gtk_label_set_text(GTK_LABEL(thongbao),"Thông báo:__________________________________\n\n        -Thêm từ thành công.");
		}
		
	}
	gtk_widget_show_all(window);
}

void window_add(GtkWidget *widget) {
	GtkBuilder *builder;
	GtkWidget *window_add;
	GtkWidget *btn_add2;
	builder = gtk_builder_new();
	gtk_builder_add_from_file(builder, "library/data/giaodien.glade", NULL);
	window_add = GTK_WIDGET(gtk_builder_get_object(builder, "window_add"));
	gtk_window_set_title (GTK_WINDOW (window_add), "Add");
	add_tu = GTK_WIDGET(gtk_builder_get_object(builder, "add_tu"));
	add_nghia = GTK_WIDGET(gtk_builder_get_object(builder, "add_nghia"));
	btn_add2 = GTK_WIDGET(gtk_builder_get_object(builder, "btn_add2"));
	g_signal_connect(G_OBJECT(btn_add2), "clicked", G_CALLBACK(window_dialog),NULL);
	gtk_widget_show_all(window_add);

}