// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.4.2
// LVGL version: 8.3.11
// Project name: SquareLine_Project

#include "ui.h"

void ui_Screen1_screen_init(void)
{
    ui_Screen1 = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_Screen1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Image5 = lv_img_create(ui_Screen1);
    lv_img_set_src(ui_Image5, &ui_img_uvl02_png);
    lv_obj_set_width(ui_Image5, 250);
    lv_obj_set_height(ui_Image5, 230);
    lv_obj_set_y(ui_Image5, -100);
    lv_obj_set_x(ui_Image5, lv_pct(-38));
    lv_obj_set_align(ui_Image5, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Image5, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_Image5, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_img_set_zoom(ui_Image5, 200);

    ui_Image1 = lv_img_create(ui_Screen1);
    lv_img_set_src(ui_Image1, &ui_img_uvl02_png);
    lv_obj_set_width(ui_Image1, 250);
    lv_obj_set_height(ui_Image1, 230);
    lv_obj_set_x(ui_Image1, -104);
    lv_obj_set_y(ui_Image1, -100);
    lv_obj_set_align(ui_Image1, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Image1, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_Image1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_img_set_zoom(ui_Image1, 200);

    ui_Image3 = lv_img_create(ui_Screen1);
    lv_img_set_src(ui_Image3, &ui_img_uvl02_png);
    lv_obj_set_width(ui_Image3, 250);
    lv_obj_set_height(ui_Image3, 230);
    lv_obj_set_x(ui_Image3, 97);
    lv_obj_set_y(ui_Image3, -100);
    lv_obj_set_align(ui_Image3, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Image3, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_Image3, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_img_set_zoom(ui_Image3, 200);

    ui_Image4 = lv_img_create(ui_Screen1);
    lv_img_set_src(ui_Image4, &ui_img_uvl02_png);
    lv_obj_set_width(ui_Image4, 250);
    lv_obj_set_height(ui_Image4, 230);
    lv_obj_set_x(ui_Image4, 298);
    lv_obj_set_y(ui_Image4, -100);
    lv_obj_set_align(ui_Image4, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Image4, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_Image4, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_img_set_zoom(ui_Image4, 200);

    ui_Image6 = lv_img_create(ui_Screen1);
    lv_img_set_src(ui_Image6, &ui_img_uvl02_png);
    lv_obj_set_width(ui_Image6, 250);
    lv_obj_set_height(ui_Image6, 230);
    lv_obj_set_x(ui_Image6, -302);
    lv_obj_set_y(ui_Image6, 87);
    lv_obj_set_align(ui_Image6, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Image6, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_Image6, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_img_set_zoom(ui_Image6, 200);

    ui_Image7 = lv_img_create(ui_Screen1);
    lv_img_set_src(ui_Image7, &ui_img_uvl02_png);
    lv_obj_set_width(ui_Image7, 250);
    lv_obj_set_height(ui_Image7, 230);
    lv_obj_set_x(ui_Image7, -105);
    lv_obj_set_y(ui_Image7, 86);
    lv_obj_set_align(ui_Image7, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Image7, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_Image7, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_img_set_zoom(ui_Image7, 200);

    ui_Image8 = lv_img_create(ui_Screen1);
    lv_img_set_src(ui_Image8, &ui_img_uvl02_png);
    lv_obj_set_width(ui_Image8, 250);
    lv_obj_set_height(ui_Image8, 230);
    lv_obj_set_x(ui_Image8, 93);
    lv_obj_set_y(ui_Image8, 85);
    lv_obj_set_align(ui_Image8, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Image8, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_Image8, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_img_set_zoom(ui_Image8, 200);

    ui_Image9 = lv_img_create(ui_Screen1);
    lv_img_set_src(ui_Image9, &ui_img_uvl02_png);
    lv_obj_set_width(ui_Image9, 250);
    lv_obj_set_height(ui_Image9, 230);
    lv_obj_set_x(ui_Image9, 290);
    lv_obj_set_y(ui_Image9, 85);
    lv_obj_set_align(ui_Image9, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Image9, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_Image9, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_img_set_zoom(ui_Image9, 200);

    ui_Label1 = lv_label_create(ui_Screen1);
    lv_obj_set_width(ui_Label1, lv_pct(5));
    lv_obj_set_height(ui_Label1, lv_pct(5));
    lv_obj_set_x(ui_Label1, -223);
    lv_obj_set_y(ui_Label1, -75);
    lv_obj_set_align(ui_Label1, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label1, "L1");

    ui_Label2 = lv_label_create(ui_Screen1);
    lv_obj_set_width(ui_Label2, lv_pct(5));
    lv_obj_set_height(ui_Label2, lv_pct(5));
    lv_obj_set_x(ui_Label2, -24);
    lv_obj_set_y(ui_Label2, -77);
    lv_obj_set_align(ui_Label2, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label2, "L2");

    ui_Label3 = lv_label_create(ui_Screen1);
    lv_obj_set_width(ui_Label3, lv_pct(5));
    lv_obj_set_height(ui_Label3, lv_pct(5));
    lv_obj_set_x(ui_Label3, 177);
    lv_obj_set_y(ui_Label3, -75);
    lv_obj_set_align(ui_Label3, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label3, "L3");

    ui_Label4 = lv_label_create(ui_Screen1);
    lv_obj_set_width(ui_Label4, lv_pct(5));
    lv_obj_set_height(ui_Label4, lv_pct(5));
    lv_obj_set_x(ui_Label4, 377);
    lv_obj_set_y(ui_Label4, -74);
    lv_obj_set_align(ui_Label4, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label4, "L4");

    ui_Bar1 = lv_bar_create(ui_Screen1);
    lv_bar_set_value(ui_Bar1, 25, LV_ANIM_OFF);
    lv_bar_set_start_value(ui_Bar1, 0, LV_ANIM_OFF);
    lv_obj_set_width(ui_Bar1, 150);
    lv_obj_set_height(ui_Bar1, 10);
    lv_obj_set_x(ui_Bar1, -278);
    lv_obj_set_y(ui_Bar1, 0);
    lv_obj_set_align(ui_Bar1, LV_ALIGN_CENTER);

    ui_Label5 = lv_label_create(ui_Screen1);
    lv_obj_set_width(ui_Label5, lv_pct(5));
    lv_obj_set_height(ui_Label5, lv_pct(5));
    lv_obj_set_x(ui_Label5, -221);
    lv_obj_set_y(ui_Label5, 167);
    lv_obj_set_align(ui_Label5, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label5, "L5");

    ui_Label6 = lv_label_create(ui_Screen1);
    lv_obj_set_width(ui_Label6, lv_pct(5));
    lv_obj_set_height(ui_Label6, lv_pct(5));
    lv_obj_set_x(ui_Label6, -27);
    lv_obj_set_y(ui_Label6, 166);
    lv_obj_set_align(ui_Label6, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label6, "L6");

    ui_Label7 = lv_label_create(ui_Screen1);
    lv_obj_set_width(ui_Label7, lv_pct(5));
    lv_obj_set_height(ui_Label7, lv_pct(5));
    lv_obj_set_x(ui_Label7, 171);
    lv_obj_set_y(ui_Label7, 166);
    lv_obj_set_align(ui_Label7, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label7, "L7");

    ui_Label8 = lv_label_create(ui_Screen1);
    lv_obj_set_width(ui_Label8, lv_pct(5));
    lv_obj_set_height(ui_Label8, lv_pct(5));
    lv_obj_set_x(ui_Label8, 369);
    lv_obj_set_y(ui_Label8, 167);
    lv_obj_set_align(ui_Label8, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label8, "L8");

    ui_Bar2 = lv_bar_create(ui_Screen1);
    lv_bar_set_value(ui_Bar2, 25, LV_ANIM_OFF);
    lv_bar_set_start_value(ui_Bar2, 0, LV_ANIM_OFF);
    lv_obj_set_width(ui_Bar2, 150);
    lv_obj_set_height(ui_Bar2, 10);
    lv_obj_set_x(ui_Bar2, -80);
    lv_obj_set_y(ui_Bar2, 0);
    lv_obj_set_align(ui_Bar2, LV_ALIGN_CENTER);

    ui_Bar3 = lv_bar_create(ui_Screen1);
    lv_bar_set_value(ui_Bar3, 25, LV_ANIM_OFF);
    lv_bar_set_start_value(ui_Bar3, 0, LV_ANIM_OFF);
    lv_obj_set_width(ui_Bar3, 150);
    lv_obj_set_height(ui_Bar3, 10);
    lv_obj_set_x(ui_Bar3, 125);
    lv_obj_set_y(ui_Bar3, 0);
    lv_obj_set_align(ui_Bar3, LV_ALIGN_CENTER);

    ui_Bar4 = lv_bar_create(ui_Screen1);
    lv_bar_set_value(ui_Bar4, 25, LV_ANIM_OFF);
    lv_bar_set_start_value(ui_Bar4, 0, LV_ANIM_OFF);
    lv_obj_set_width(ui_Bar4, 150);
    lv_obj_set_height(ui_Bar4, 10);
    lv_obj_set_x(ui_Bar4, 320);
    lv_obj_set_y(ui_Bar4, 0);
    lv_obj_set_align(ui_Bar4, LV_ALIGN_CENTER);

    ui_Bar5 = lv_bar_create(ui_Screen1);
    lv_bar_set_value(ui_Bar5, 25, LV_ANIM_OFF);
    lv_bar_set_start_value(ui_Bar5, 0, LV_ANIM_OFF);
    lv_obj_set_width(ui_Bar5, 150);
    lv_obj_set_height(ui_Bar5, 10);
    lv_obj_set_x(ui_Bar5, -277);
    lv_obj_set_y(ui_Bar5, 197);
    lv_obj_set_align(ui_Bar5, LV_ALIGN_CENTER);

    ui_Bar6 = lv_bar_create(ui_Screen1);
    lv_bar_set_value(ui_Bar6, 25, LV_ANIM_OFF);
    lv_bar_set_start_value(ui_Bar6, 0, LV_ANIM_OFF);
    lv_obj_set_width(ui_Bar6, 150);
    lv_obj_set_height(ui_Bar6, 10);
    lv_obj_set_x(ui_Bar6, -81);
    lv_obj_set_y(ui_Bar6, 197);
    lv_obj_set_align(ui_Bar6, LV_ALIGN_CENTER);

    ui_Bar7 = lv_bar_create(ui_Screen1);
    lv_bar_set_value(ui_Bar7, 25, LV_ANIM_OFF);
    lv_bar_set_start_value(ui_Bar7, 0, LV_ANIM_OFF);
    lv_obj_set_width(ui_Bar7, 150);
    lv_obj_set_height(ui_Bar7, 10);
    lv_obj_set_x(ui_Bar7, 119);
    lv_obj_set_y(ui_Bar7, 197);
    lv_obj_set_align(ui_Bar7, LV_ALIGN_CENTER);

    ui_Bar8 = lv_bar_create(ui_Screen1);
    lv_bar_set_value(ui_Bar8, 25, LV_ANIM_OFF);
    lv_bar_set_start_value(ui_Bar8, 0, LV_ANIM_OFF);
    lv_obj_set_width(ui_Bar8, 150);
    lv_obj_set_height(ui_Bar8, 10);
    lv_obj_set_x(ui_Bar8, 319);
    lv_obj_set_y(ui_Bar8, 197);
    lv_obj_set_align(ui_Bar8, LV_ALIGN_CENTER);

    ui_Button1 = lv_btn_create(ui_Screen1);
    lv_obj_set_width(ui_Button1, 94);
    lv_obj_set_height(ui_Button1, 50);
    lv_obj_set_x(ui_Button1, -140);
    lv_obj_set_y(ui_Button1, -214);
    lv_obj_set_align(ui_Button1, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Button1, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_Button1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Label9 = lv_label_create(ui_Button1);
    lv_obj_set_width(ui_Label9, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label9, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Label9, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label9, "Refresh");

    ui_Button2 = lv_btn_create(ui_Screen1);
    lv_obj_set_width(ui_Button2, 100);
    lv_obj_set_height(ui_Button2, 50);
    lv_obj_set_x(ui_Button2, -14);
    lv_obj_set_y(ui_Button2, -214);
    lv_obj_set_align(ui_Button2, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Button2, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_Button2, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Label10 = lv_label_create(ui_Button2);
    lv_obj_set_width(ui_Label10, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label10, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Label10, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label10, "LOG");

    lv_obj_add_event_cb(ui_Button1, ui_event_Button1, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_Button2, ui_event_Button2, LV_EVENT_ALL, NULL);

}
