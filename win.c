/*登录窗口pass.c*/
#include<gtk/gtk.h>

	//定义2个输入控件指针变量
	
	static GtkWidget* user_name;
	static GtkWidget* user_password;
	GtkWidget* tmp_window;
//点击“确认”按钮的回调函数

GtkWidget *create_login_window(GtkWidget * window, const gchar *tiltle, gint width, gint high, gboolean background,  gpointer data);
GtkWidget *create_main_window(GtkWidget * window, const gchar *tiltle, gint width, gint high, gboolean background,  gpointer data);



void on_button_clicked(GtkWidget* button,gpointer data)
{
	//获取2个输入框的信息
	 const gchar *username = gtk_entry_get_text(GTK_ENTRY(user_name));
	 const gchar *password = gtk_entry_get_text(GTK_ENTRY(user_password));
	//输出2个输入框的信息
	g_print("用户名是:%s",username);
	g_print("\n");
	g_print("密  码是:%s",password);
	g_print("\n");
}

void on_login_button_clicked(GtkWidget* button,gpointer data)
{	
	GtkWidget* window = (GtkWidget*)data;
	window = create_main_window(window, "聊天程序",800,600,TRUE,NULL);
	gtk_widget_show_all(window);
}

/*---------------------------------背景图片-----------------------------------------------*/

void update_widget_bg(GtkWidget *widget, gchar *img_file) //gtk2
{       
	GtkStyle *style;     
	GdkPixbuf *pixbuf;       
	GdkPixmap *pixmap;     
	gint width, height;    

	pixbuf = gdk_pixbuf_new_from_file(img_file, NULL);    
	width = gdk_pixbuf_get_width(pixbuf);   
	height = gdk_pixbuf_get_height(pixbuf);    
	pixmap = gdk_pixmap_new(NULL, width, height, 24);   
	gdk_pixbuf_render_pixmap_and_mask(pixbuf, &pixmap, NULL, 0);
	style = gtk_style_copy(GTK_WIDGET (widget)->style);    

	if (style->bg_pixmap[GTK_STATE_NORMAL])        
		g_object_unref(style->bg_pixmap[GTK_STATE_NORMAL]);    

	style->bg_pixmap[GTK_STATE_NORMAL] = g_object_ref(pixmap);    
	style->bg_pixmap[GTK_STATE_ACTIVE] = g_object_ref(pixmap);
	style->bg_pixmap[GTK_STATE_PRELIGHT] = g_object_ref(pixmap);
	style->bg_pixmap[GTK_STATE_SELECTED] = g_object_ref(pixmap);
	style->bg_pixmap[GTK_STATE_INSENSITIVE] = g_object_ref(pixmap);
	gtk_widget_set_style(GTK_WIDGET (widget), style);
	g_object_unref(style);
}
/*---------------------------------end-----------------------------------------------*/

//---------------------------------------创建菜单------------------------------
GtkWidget * create_menu(GtkWidget * window, GtkWidget *menu_bar)// (GtkWidget *box, GtkAccelGroup *group)
 {
 	
	//GtkWidget *menu_bar;
	GtkWidget *file_menu;	
	GtkWidget *edit_menu;	
	GtkWidget *help_menu;
	GtkWidget *menu_item;	
	GtkWidget *menu_name;
	GtkAccelGroup* accel_group ;
	//创建菜单需要的快捷方式
	accel_group = gtk_accel_group_new( );//GtkAccelGroup *group = gtk_accel_group_new();
	gtk_window_add_accel_group(GTK_WINDOW(window),accel_group);
	
	//创建菜单条
	menu_bar = gtk_menu_bar_new();
	
	//update_widget_bg(menubar,"../bg.jpg");
	//gtk_widget_show(menubar);
	
	//创建菜单项
	//----------------------------------------------------文件菜单--------------------------------------------------------------
	file_menu = gtk_menu_new();
	//新建
	menu_item = gtk_image_menu_item_new_from_stock(GTK_STOCK_NEW, accel_group);	
	gtk_menu_shell_append(GTK_MENU_SHELL(file_menu),menu_item);
	//打开
	menu_item = gtk_image_menu_item_new_from_stock(GTK_STOCK_OPEN, accel_group);	
	gtk_menu_shell_append(GTK_MENU_SHELL(file_menu),menu_item);
	//保存
	menu_item = gtk_image_menu_item_new_from_stock(GTK_STOCK_SAVE, accel_group);	
	gtk_menu_shell_append(GTK_MENU_SHELL(file_menu),menu_item);
	//另存
	menu_item = gtk_image_menu_item_new_from_stock(GTK_STOCK_SAVE_AS, accel_group);	
	gtk_menu_shell_append(GTK_MENU_SHELL(file_menu),menu_item);
	//创建菜单中的横线
	menu_item = gtk_separator_menu_item_new();
	gtk_menu_shell_append(GTK_MENU_SHELL(file_menu),menu_item);
	//退出
	menu_item = gtk_image_menu_item_new_from_stock(GTK_STOCK_QUIT, accel_group);	
	gtk_menu_shell_append(GTK_MENU_SHELL(file_menu),menu_item);
	g_signal_connect_swapped(G_OBJECT(menu_item), "activate", G_CALLBACK(gtk_main_quit), NULL);
	//g_signal_connect_swapped(G_OBJECT(menu_item), "activate", G_CALLBACK(on_menu_activate), (gpointer)("exit"));
	 
	 //菜单分类
	menu_name = gtk_menu_item_new_with_label("文件");
	//菜单链接到分类
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(menu_name),file_menu);
	//分类添加到菜单条
	gtk_menu_bar_append(GTK_MENU_BAR(menu_bar),menu_name);
	
	//--------------------------------------------------编辑菜单---------------------------------------------------------------------
	edit_menu = gtk_menu_new();
	//剪切
	menu_item = gtk_image_menu_item_new_from_stock(GTK_STOCK_CUT, accel_group);	
	gtk_menu_shell_append(GTK_MENU_SHELL(edit_menu),menu_item);
	//复制
	menu_item = gtk_image_menu_item_new_from_stock(GTK_STOCK_COPY, accel_group);	
	gtk_menu_shell_append(GTK_MENU_SHELL(edit_menu),menu_item);
	//粘贴
	menu_item = gtk_image_menu_item_new_from_stock(GTK_STOCK_PASTE, accel_group);	
	gtk_menu_shell_append(GTK_MENU_SHELL(edit_menu),menu_item);
	//查找
	menu_item = gtk_image_menu_item_new_from_stock(GTK_STOCK_FIND, accel_group);	
	gtk_menu_shell_append(GTK_MENU_SHELL(edit_menu),menu_item);
	
	menu_name = gtk_menu_item_new_with_label("编辑");
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(menu_name),edit_menu);
	gtk_menu_bar_append(GTK_MENU_BAR(menu_bar),menu_name);
	
	//--------------------------------------------------帮助菜单----------------------------------------------------------------
	help_menu = gtk_menu_new();
	//帮助
	menu_item = gtk_image_menu_item_new_from_stock(GTK_STOCK_HELP, accel_group);	
	gtk_menu_shell_append(GTK_MENU_SHELL(help_menu),menu_item);
	//关于	
	menu_item = gtk_image_menu_item_new_from_stock(GTK_STOCK_ABOUT, accel_group);	
	gtk_menu_shell_append(GTK_MENU_SHELL(help_menu),menu_item);
	
	
	menu_name = gtk_menu_item_new_with_label("帮助");
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(menu_name),help_menu);
	gtk_menu_bar_append(GTK_MENU_BAR(menu_bar),menu_name);
	
	return menu_bar;
	
 }
 //------------------------------------------------------------end---------------------------------------------------------------
 
 //------------------------------------------------------------创建工具条---------------------------------------------------------------
GtkWidget *create_toolbar(GtkWidget * toolbar, gpointer data)
 {
 	
 	GtkWidget *entry;
 	GtkWidget *label;
 	
 	toolbar = gtk_toolbar_new( );
 	
 	gtk_toolbar_insert_stock(GTK_TOOLBAR(toolbar),GTK_STOCK_NEW,"新建一个文件","新建",GTK_SIGNAL_FUNC(on_button_clicked),(gpointer)("新建"),-1);
	gtk_toolbar_insert_stock(GTK_TOOLBAR(toolbar),GTK_STOCK_OPEN,"打开一个文件","打开",GTK_SIGNAL_FUNC(on_button_clicked),(gpointer)("打开"),-1);
	gtk_toolbar_insert_stock(GTK_TOOLBAR(toolbar),GTK_STOCK_SAVE,"保存当前文件","保存",GTK_SIGNAL_FUNC(on_button_clicked),(gpointer)("保存"),-1);
	
	gtk_toolbar_append_space(GTK_TOOLBAR(toolbar));
	
	gtk_toolbar_insert_stock(GTK_TOOLBAR(toolbar),GTK_STOCK_UNDO,"撤销刚才的修改","撤销",GTK_SIGNAL_FUNC(on_button_clicked),(gpointer)("撤销"),-1);
	gtk_toolbar_insert_stock(GTK_TOOLBAR(toolbar),GTK_STOCK_REDO,"恢复刚才的修改","重做",GTK_SIGNAL_FUNC(on_button_clicked),(gpointer)("重做"),-1);
	gtk_toolbar_insert_stock(GTK_TOOLBAR(toolbar),GTK_STOCK_REFRESH,"刷新信息","刷新",GTK_SIGNAL_FUNC(on_button_clicked),(gpointer)("刷新"),-1);
	
	gtk_toolbar_append_space(GTK_TOOLBAR(toolbar));
	
	gtk_toolbar_insert_stock(GTK_TOOLBAR(toolbar),GTK_STOCK_CUT,"剪切","剪切",GTK_SIGNAL_FUNC(on_button_clicked),(gpointer)("剪切"),-1);
	gtk_toolbar_insert_stock(GTK_TOOLBAR(toolbar),GTK_STOCK_COPY,"复制","复制",GTK_SIGNAL_FUNC(on_button_clicked),(gpointer)("复制"),-1);
	gtk_toolbar_insert_stock(GTK_TOOLBAR(toolbar),GTK_STOCK_PASTE,"粘贴","粘贴",GTK_SIGNAL_FUNC(on_button_clicked),(gpointer)("粘贴"),-1);
	gtk_toolbar_insert_stock(GTK_TOOLBAR(toolbar),GTK_STOCK_SPELL_CHECK,"拼写检查","检查",GTK_SIGNAL_FUNC(on_button_clicked),(gpointer)("退出"),-1);
	
	gtk_toolbar_append_space(GTK_TOOLBAR(toolbar));
	
	label = gtk_label_new("文件：");
	gtk_toolbar_append_widget(GTK_TOOLBAR(toolbar),label,"这是一个标签","标签");
	entry = gtk_entry_new();
	gtk_toolbar_append_widget(GTK_TOOLBAR(toolbar),entry,"这是一个录入条","录入");
	
	gtk_toolbar_insert_stock(GTK_TOOLBAR(toolbar),GTK_STOCK_FIND,"搜索文本","搜索",GTK_SIGNAL_FUNC(on_button_clicked),(gpointer)("退出"),-1);
	gtk_toolbar_insert_stock(GTK_TOOLBAR(toolbar),GTK_STOCK_FIND_AND_REPLACE,"搜索文本","搜索",GTK_SIGNAL_FUNC(on_button_clicked),(gpointer)("退出"),-1);
	


	//设定工具条的外观,GTK_TOOLBAR_ICONS表示只显示图标
	gtk_toolbar_set_style(GTK_TOOLBAR(toolbar),GTK_TOOLBAR_ICONS);
	//设定工具条中图标大小，GTK_ICON_SIZE_SMALL_TOOLBAR表示工具条中使用小图标；
	gtk_toolbar_set_icon_size(GTK_TOOLBAR(toolbar),GTK_ICON_SIZE_SMALL_TOOLBAR);
	
	return toolbar;
 }

//------------------------------------------------------------end---------------------------------------------------------------





//------------------------------------------------------------初始化窗口---------------------------------------------------------------

GtkWidget *init_window(GtkWidget * window, const gchar *tiltle, gint width, gint high, gboolean background)
 {
 	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window),tiltle);
	gtk_window_set_default_size(GTK_WINDOW(window),width, high);
	gtk_window_set_resizable(GTK_WINDOW(window), TRUE);
	gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
	gtk_container_set_border_width(GTK_CONTAINER(window),0);
	
	if(background)
		update_widget_bg(window,"../bg.jpg");//准备用宏
	gtk_widget_show(window);
	//g_signal_connect(G_OBJECT(window),"destroy",G_CALLBACK(gtk_widget_destroy(window)),NULL);
	return window;
 }

//------------------------------------------------------------创建login窗口---------------------------------------------------------------
GtkWidget *create_login_window(GtkWidget * window, const gchar *tiltle, gint width, gint high, gboolean background,  gpointer data)
 {
 	GtkWidget* align		= NULL;
	GtkWidget* vbox		= NULL;
	GtkWidget* table		= NULL;
	GtkWidget* hbox1		= NULL;
	GtkWidget* hbox2		= NULL;
	GtkWidget* hbox3		= NULL;
	GtkWidget* label1		= NULL;
	GtkWidget* label2		= NULL;
	GtkWidget* button		= NULL;
	GtkWidget* sep		= NULL;
	
	window = init_window(window, tiltle, width, high,  background);
	
	//布局
	align = gtk_alignment_new(0.5,0.5,0,0);
	
	gtk_container_add(GTK_CONTAINER(window),align);
	
	
	vbox = gtk_vbox_new(FALSE,0);
	gtk_container_add(GTK_CONTAINER(align),vbox);
	hbox1 = gtk_hbox_new(FALSE,0);
	gtk_box_pack_start(GTK_BOX(vbox),hbox1,FALSE,FALSE,5);
	hbox2 = gtk_hbox_new(FALSE,0);
	gtk_box_pack_start(GTK_BOX(vbox),hbox2,FALSE,FALSE,5);

	hbox3 = gtk_hbox_new(FALSE,0);
	gtk_box_pack_start(GTK_BOX(vbox),hbox3,FALSE,FALSE,5);
	
	table = gtk_table_new(1,7,TRUE);

	gtk_box_pack_start(GTK_BOX(hbox3), table,FALSE, FALSE,0);

	sep = gtk_hseparator_new();//横向分割线
	gtk_box_pack_start(GTK_BOX(vbox),sep,FALSE,FALSE,5);


	label1 = gtk_label_new("用户名:");
	user_name = gtk_entry_new();
	//按从前到后顺序在一个横向盒子中排列这个标签和输入框
	gtk_box_pack_start(GTK_BOX(hbox1),label1,FALSE,FALSE,5);
	gtk_box_pack_start(GTK_BOX(hbox1),user_name,FALSE,FALSE,5);

	label2= gtk_label_new("密     码:");
	user_password = gtk_entry_new();
	//单行输入控件的显示属性，FALSE表示显示的内容全部是
	gtk_entry_set_visibility(GTK_ENTRY(user_password),FALSE);
	gtk_box_pack_start(GTK_BOX(hbox2),label2,FALSE,FALSE,5);
	gtk_box_pack_start(GTK_BOX(hbox2),user_password,FALSE,FALSE,5);
	
	//注册
	button = gtk_button_new_with_label("注册");
	g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(on_button_clicked),NULL);
	//g_signal_connect_swapped(G_OBJECT(button),"clicked",G_CALLBACK(gtk_widget_destroy),window);//不能点完了就直接销毁
	gtk_table_attach(GTK_TABLE(table), button ,2, 3 ,0 ,1, GTK_FILL, GTK_FILL, 0 , 0);
	
	//登陆
	button = gtk_button_new_with_label("登陆");
	g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(on_button_clicked),NULL);
	g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(on_login_button_clicked),data);
	
	g_signal_connect_swapped(G_OBJECT(button),"clicked",G_CALLBACK(gtk_widget_destroy),window);
	gtk_table_attach(GTK_TABLE(table), button ,4 , 5 ,0 ,1, GTK_FILL, GTK_FILL, 0 , 0);

	//只销毁单个窗体，不退出
	//g_signal_connect(G_OBJECT(window),"destroy",G_CALLBACK(gtk_widget_destroy),window);
	
	g_signal_connect(G_OBJECT(window),"destroy",G_CALLBACK(gtk_main_quit),window);
	//创建完后，把窗体里面的全部表现出来
	gtk_widget_show_all(window);
	return window;
 }

GtkWidget *create_main_window(GtkWidget * window, const gchar *tiltle, gint width, gint high, gboolean background, gpointer data)
 {
 	GtkWidget *	vbox	 = NULL;
	GtkWidget *	menubar	 = NULL;
	GtkWidget *	toolbar	 = NULL;
	GtkWidget *	text		 = NULL;
	GtkWidget *	align	 = NULL;
	GtkWidget *	scrolled	 = NULL;
		
	window = init_window(window, tiltle, width, high,  background);
	
	//布局
	vbox = gtk_vbox_new(FALSE,0);
	gtk_container_add(GTK_CONTAINER(window),vbox);
	
	//创建菜单函数
	menubar = create_menu(window, menubar); //貌似不安全
	gtk_box_pack_start(GTK_BOX(vbox),menubar,FALSE,FALSE,0);
	
	
	//创建工具条
	toolbar = create_toolbar(toolbar, NULL);
	gtk_box_pack_start(GTK_BOX(vbox),toolbar,FALSE,FALSE,0);	
	
	scrolled=gtk_scrolled_window_new(NULL,NULL);
	text = gtk_text_view_new();
	gtk_box_pack_start(GTK_BOX(vbox),text,FALSE,FALSE,0);
	gtk_text_view_set_editable(GTK_TEXT_VIEW(text), TRUE);
	//gtk_text_view_set_cursor_visible(GTK_TEXT_VIEW(text ), TRUE);
	
	//gtk_box_pack_start(GTK_BOX(vbox),scrolled,FALSE,FALSE,0);
	//gtk_container_add(GTK_CONTAINER(scrolled), text);
	
	
	//align = gtk_alignment_new(1,1,1,1);  
	//gtk_container_add(GTK_CONTAINER(align),text);  
	//gtk_container_add(GTK_CONTAINER(window),align);  
	
	gtk_widget_hide(window);
	//gtk_widget_show_all(window);
	return window;
 }



//主函数
int main(int argc,char* argv[])
{
	//定义多个窗口控件指针变量
	//GtkWidget* window			= NULL;		//主窗口
	GtkWidget* main_window		= NULL;		
	GtkWidget* login				= NULL;		//登录窗口

	//初始化
	gtk_init(&argc,&argv);

	//创建一个新窗口
	login = create_login_window(login, "登录",350,200,TRUE, main_window);//typedef void* gpointer;
	//main_window = create_main_window(main_window, "聊天程序",800,600,TRUE,NULL);
	//gtk_widget_show_all(login);
	//login = init_window(login, "登录",300, 300,FALSE);
	
	/*----------------------------------------------------------------------------------------------------------------------*/
	

	//显示所用控件
	//gtk_widget_show_all(login);
	gtk_main();
	return FALSE;
}
