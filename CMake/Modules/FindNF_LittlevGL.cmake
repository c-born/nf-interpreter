# CMakeList.txt : CMake project for LittlevGL, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# TODO: Add tests and install targets if needed.

# LittlevGL core
#__________________
list(APPEND littlevGL_Sources "${PROJECT_SOURCE_DIR}/src/LittlevGL/lvgl/lv_core/lv_group.c")
list(APPEND littlevGL_Sources "${PROJECT_SOURCE_DIR}/src/LittlevGL/lvgl/lv_core/lv_indev.c")
list(APPEND littlevGL_Sources "${PROJECT_SOURCE_DIR}/src/LittlevGL/lvgl/lv_core/lv_lang.c")
list(APPEND littlevGL_Sources "${PROJECT_SOURCE_DIR}/src/LittlevGL/lvgl/lv_core/lv_obj.c")
list(APPEND littlevGL_Sources "${PROJECT_SOURCE_DIR}/src/LittlevGL/lvgl/lv_core/lv_refr.c")
list(APPEND littlevGL_Sources "${PROJECT_SOURCE_DIR}/src/LittlevGL/lvgl/lv_core/lv_style.c")
list(APPEND littlevGL_Sources "${PROJECT_SOURCE_DIR}/src/LittlevGL/lvgl/lv_core/lv_vdb.c")
list(APPEND littlevGL_Sources "${PROJECT_SOURCE_DIR}/src/LittlevGL/lvgl/lv_draw/lv_draw.c")
list(APPEND littlevGL_Sources "${PROJECT_SOURCE_DIR}/src/LittlevGL/lvgl/lv_draw/lv_draw_arc.c")
list(APPEND littlevGL_Sources "${PROJECT_SOURCE_DIR}/src/LittlevGL/lvgl/lv_draw/lv_draw_img.c")
list(APPEND littlevGL_Sources "${PROJECT_SOURCE_DIR}/src/LittlevGL/lvgl/lv_draw/lv_draw_label.c")
list(APPEND littlevGL_Sources "${PROJECT_SOURCE_DIR}/src/LittlevGL/lvgl/lv_draw/lv_draw_line.c")
list(APPEND littlevGL_Sources "${PROJECT_SOURCE_DIR}/src/LittlevGL/lvgl/lv_draw/lv_draw_rbasic.c")
list(APPEND littlevGL_Sources "${PROJECT_SOURCE_DIR}/src/LittlevGL/lvgl/lv_draw/lv_draw_rect.c")
list(APPEND littlevGL_Sources "${PROJECT_SOURCE_DIR}/src/LittlevGL/lvgl/lv_draw/lv_draw_triangle.c")
list(APPEND littlevGL_Sources "${PROJECT_SOURCE_DIR}/src/LittlevGL/lvgl/lv_draw/lv_draw_vbasic.c")
list(APPEND littlevGL_Sources "${PROJECT_SOURCE_DIR}/src/LittlevGL/lvgl/lv_fonts/lv_font_builtin.c")
list(APPEND littlevGL_Sources "${PROJECT_SOURCE_DIR}/src/LittlevGL/lvgl/lv_fonts/lv_font_dejavu_10.c")
list(APPEND littlevGL_Sources "${PROJECT_SOURCE_DIR}/src/LittlevGL/lvgl/lv_fonts/lv_font_dejavu_10_cyrillic.c")
list(APPEND littlevGL_Sources "${PROJECT_SOURCE_DIR}/src/LittlevGL/lvgl/lv_fonts/lv_font_dejavu_10_latin_sup.c")
list(APPEND littlevGL_Sources "${PROJECT_SOURCE_DIR}/src/LittlevGL/lvgl/lv_fonts/lv_font_dejavu_20.c")
list(APPEND littlevGL_Sources "${PROJECT_SOURCE_DIR}/src/LittlevGL/lvgl/lv_fonts/lv_font_dejavu_20_cyrillic.c")
list(APPEND littlevGL_Sources "${PROJECT_SOURCE_DIR}/src/LittlevGL/lvgl/lv_fonts/lv_font_dejavu_20_latin_sup.c")
list(APPEND littlevGL_Sources "${PROJECT_SOURCE_DIR}/src/LittlevGL/lvgl/lv_fonts/lv_font_dejavu_30.c")
list(APPEND littlevGL_Sources "${PROJECT_SOURCE_DIR}/src/LittlevGL/lvgl/lv_fonts/lv_font_dejavu_30_cyrillic.c")
list(APPEND littlevGL_Sources "${PROJECT_SOURCE_DIR}/src/LittlevGL/lvgl/lv_fonts/lv_font_dejavu_30_latin_sup.c")
list(APPEND littlevGL_Sources "${PROJECT_SOURCE_DIR}/src/LittlevGL/lvgl/lv_fonts/lv_font_dejavu_40.c")
list(APPEND littlevGL_Sources "${PROJECT_SOURCE_DIR}/src/LittlevGL/lvgl/lv_fonts/lv_font_dejavu_40_cyrillic.c")
list(APPEND littlevGL_Sources "${PROJECT_SOURCE_DIR}/src/LittlevGL/lvgl/lv_fonts/lv_font_dejavu_40_latin_sup.c")
list(APPEND littlevGL_Sources "${PROJECT_SOURCE_DIR}/src/LittlevGL/lvgl/lv_fonts/lv_font_monospace_8.c")
list(APPEND littlevGL_Sources "${PROJECT_SOURCE_DIR}/src/LittlevGL/lvgl/lv_fonts/lv_font_symbol_10.c")
list(APPEND littlevGL_Sources "${PROJECT_SOURCE_DIR}/src/LittlevGL/lvgl/lv_fonts/lv_font_symbol_20.c")
list(APPEND littlevGL_Sources "${PROJECT_SOURCE_DIR}/src/LittlevGL/lvgl/lv_fonts/lv_font_symbol_30.c")
list(APPEND littlevGL_Sources "${PROJECT_SOURCE_DIR}/src/LittlevGL/lvgl/lv_fonts/lv_font_symbol_40.c")
list(APPEND littlevGL_Sources "${PROJECT_SOURCE_DIR}/src/LittlevGL/lvgl/lv_hal/lv_hal_disp.c")
list(APPEND littlevGL_Sources "${PROJECT_SOURCE_DIR}/src/LittlevGL/lvgl/lv_hal/lv_hal_indev.c")
list(APPEND littlevGL_Sources "${PROJECT_SOURCE_DIR}/src/LittlevGL/lvgl/lv_hal/lv_hal_tick.c")
list(APPEND littlevGL_Sources "${PROJECT_SOURCE_DIR}/src/LittlevGL/lvgl/lv_misc/lv_anim.c")
list(APPEND littlevGL_Sources "${PROJECT_SOURCE_DIR}/src/LittlevGL/lvgl/lv_misc/lv_area.c")
list(APPEND littlevGL_Sources "${PROJECT_SOURCE_DIR}/src/LittlevGL/lvgl/lv_misc/lv_circ.c")
list(APPEND littlevGL_Sources "${PROJECT_SOURCE_DIR}/src/LittlevGL/lvgl/lv_misc/lv_color.c")
list(APPEND littlevGL_Sources "${PROJECT_SOURCE_DIR}/src/LittlevGL/lvgl/lv_misc/lv_font.c")
list(APPEND littlevGL_Sources "${PROJECT_SOURCE_DIR}/src/LittlevGL/lvgl/lv_misc/lv_fs.c")
list(APPEND littlevGL_Sources "${PROJECT_SOURCE_DIR}/src/LittlevGL/lvgl/lv_misc/lv_gc.c")
list(APPEND littlevGL_Sources "${PROJECT_SOURCE_DIR}/src/LittlevGL/lvgl/lv_misc/lv_ll.c")
list(APPEND littlevGL_Sources "${PROJECT_SOURCE_DIR}/src/LittlevGL/lvgl/lv_misc/lv_log.c")
list(APPEND littlevGL_Sources "${PROJECT_SOURCE_DIR}/src/LittlevGL/lvgl/lv_misc/lv_math.c")
list(APPEND littlevGL_Sources "${PROJECT_SOURCE_DIR}/src/LittlevGL/lvgl/lv_misc/lv_mem.c")
list(APPEND littlevGL_Sources "${PROJECT_SOURCE_DIR}/src/LittlevGL/lvgl/lv_misc/lv_task.c")
list(APPEND littlevGL_Sources "${PROJECT_SOURCE_DIR}/src/LittlevGL/lvgl/lv_misc/lv_templ.c")
list(APPEND littlevGL_Sources "${PROJECT_SOURCE_DIR}/src/LittlevGL/lvgl/lv_misc/lv_txt.c")
list(APPEND littlevGL_Sources "${PROJECT_SOURCE_DIR}/src/LittlevGL/lvgl/lv_misc/lv_ufs.c")
list(APPEND littlevGL_Sources "${PROJECT_SOURCE_DIR}/src/LittlevGL/lvgl/lv_objx/lv_arc.c")
list(APPEND littlevGL_Sources "${PROJECT_SOURCE_DIR}/src/LittlevGL/lvgl/lv_objx/lv_bar.c")
list(APPEND littlevGL_Sources "${PROJECT_SOURCE_DIR}/src/LittlevGL/lvgl/lv_objx/lv_btn.c")
list(APPEND littlevGL_Sources "${PROJECT_SOURCE_DIR}/src/LittlevGL/lvgl/lv_objx/lv_btnm.c")
list(APPEND littlevGL_Sources "${PROJECT_SOURCE_DIR}/src/LittlevGL/lvgl/lv_objx/lv_calendar.c")
list(APPEND littlevGL_Sources "${PROJECT_SOURCE_DIR}/src/LittlevGL/lvgl/lv_objx/lv_canvas.c")
list(APPEND littlevGL_Sources "${PROJECT_SOURCE_DIR}/src/LittlevGL/lvgl/lv_objx/lv_cb.c")
list(APPEND littlevGL_Sources "${PROJECT_SOURCE_DIR}/src/LittlevGL/lvgl/lv_objx/lv_chart.c")
list(APPEND littlevGL_Sources "${PROJECT_SOURCE_DIR}/src/LittlevGL/lvgl/lv_objx/lv_cont.c")
list(APPEND littlevGL_Sources "${PROJECT_SOURCE_DIR}/src/LittlevGL/lvgl/lv_objx/lv_ddlist.c")
list(APPEND littlevGL_Sources "${PROJECT_SOURCE_DIR}/src/LittlevGL/lvgl/lv_objx/lv_gauge.c")
list(APPEND littlevGL_Sources "${PROJECT_SOURCE_DIR}/src/LittlevGL/lvgl/lv_objx/lv_img.c")
list(APPEND littlevGL_Sources "${PROJECT_SOURCE_DIR}/src/LittlevGL/lvgl/lv_objx/lv_imgbtn.c")
list(APPEND littlevGL_Sources "${PROJECT_SOURCE_DIR}/src/LittlevGL/lvgl/lv_objx/lv_kb.c")
list(APPEND littlevGL_Sources "${PROJECT_SOURCE_DIR}/src/LittlevGL/lvgl/lv_objx/lv_label.c")
list(APPEND littlevGL_Sources "${PROJECT_SOURCE_DIR}/src/LittlevGL/lvgl/lv_objx/lv_led.c")
list(APPEND littlevGL_Sources "${PROJECT_SOURCE_DIR}/src/LittlevGL/lvgl/lv_objx/lv_line.c")
list(APPEND littlevGL_Sources "${PROJECT_SOURCE_DIR}/src/LittlevGL/lvgl/lv_objx/lv_list.c")
list(APPEND littlevGL_Sources "${PROJECT_SOURCE_DIR}/src/LittlevGL/lvgl/lv_objx/lv_lmeter.c")
list(APPEND littlevGL_Sources "${PROJECT_SOURCE_DIR}/src/LittlevGL/lvgl/lv_objx/lv_mbox.c")
list(APPEND littlevGL_Sources "${PROJECT_SOURCE_DIR}/src/LittlevGL/lvgl/lv_objx/lv_objx_templ.c")
list(APPEND littlevGL_Sources "${PROJECT_SOURCE_DIR}/src/LittlevGL/lvgl/lv_objx/lv_page.c")
list(APPEND littlevGL_Sources "${PROJECT_SOURCE_DIR}/src/LittlevGL/lvgl/lv_objx/lv_preload.c")
list(APPEND littlevGL_Sources "${PROJECT_SOURCE_DIR}/src/LittlevGL/lvgl/lv_objx/lv_roller.c")
list(APPEND littlevGL_Sources "${PROJECT_SOURCE_DIR}/src/LittlevGL/lvgl/lv_objx/lv_slider.c")
list(APPEND littlevGL_Sources "${PROJECT_SOURCE_DIR}/src/LittlevGL/lvgl/lv_objx/lv_spinbox.c")
list(APPEND littlevGL_Sources "${PROJECT_SOURCE_DIR}/src/LittlevGL/lvgl/lv_objx/lv_sw.c")
list(APPEND littlevGL_Sources "${PROJECT_SOURCE_DIR}/src/LittlevGL/lvgl/lv_objx/lv_ta.c")
list(APPEND littlevGL_Sources "${PROJECT_SOURCE_DIR}/src/LittlevGL/lvgl/lv_objx/lv_table.c")
list(APPEND littlevGL_Sources "${PROJECT_SOURCE_DIR}/src/LittlevGL/lvgl/lv_objx/lv_tabview.c")
list(APPEND littlevGL_Sources "${PROJECT_SOURCE_DIR}/src/LittlevGL/lvgl/lv_objx/lv_tileview.c")
list(APPEND littlevGL_Sources "${PROJECT_SOURCE_DIR}/src/LittlevGL/lvgl/lv_objx/lv_win.c")
list(APPEND littlevGL_Sources "${PROJECT_SOURCE_DIR}/src/LittlevGL/lvgl/lv_porting/lv_port_disp_templ.c")
list(APPEND littlevGL_Sources "${PROJECT_SOURCE_DIR}/src/LittlevGL/lvgl/lv_porting/lv_port_fs_templ.c")
list(APPEND littlevGL_Sources "${PROJECT_SOURCE_DIR}/src/LittlevGL/lvgl/lv_porting/lv_port_indev_templ.c")
list(APPEND littlevGL_Sources "${PROJECT_SOURCE_DIR}/src/LittlevGL/lvgl/lv_themes/lv_theme.c")
list(APPEND littlevGL_Sources "${PROJECT_SOURCE_DIR}/src/LittlevGL/lvgl/lv_themes/lv_theme_alien.c")
list(APPEND littlevGL_Sources "${PROJECT_SOURCE_DIR}/src/LittlevGL/lvgl/lv_themes/lv_theme_default.c")
list(APPEND littlevGL_Sources "${PROJECT_SOURCE_DIR}/src/LittlevGL/lvgl/lv_themes/lv_theme_material.c")
list(APPEND littlevGL_Sources "${PROJECT_SOURCE_DIR}/src/LittlevGL/lvgl/lv_themes/lv_theme_mono.c")
list(APPEND littlevGL_Sources "${PROJECT_SOURCE_DIR}/src/LittlevGL/lvgl/lv_themes/lv_theme_nemo.c")
list(APPEND littlevGL_Sources "${PROJECT_SOURCE_DIR}/src/LittlevGL/lvgl/lv_themes/lv_theme_night.c")
list(APPEND littlevGL_Sources "${PROJECT_SOURCE_DIR}/src/LittlevGL/lvgl/lv_themes/lv_theme_templ.c")
list(APPEND littlevGL_Sources "${PROJECT_SOURCE_DIR}/src/LittlevGL/lvgl/lv_themes/lv_theme_zen.c")


# Display and touch drivers (LittlegVL core)
#__________________
list(APPEND littlevGL_Sources "${PROJECT_SOURCE_DIR}/src/LittlevGL/lv_drivers/display/fbdev.c")
list(APPEND littlevGL_Sources "${PROJECT_SOURCE_DIR}/src/LittlevGL/lv_drivers/display/monitor.c")
list(APPEND littlevGL_Sources "${PROJECT_SOURCE_DIR}/src/LittlevGL/lv_drivers/display/r61581.c")
list(APPEND littlevGL_Sources "${PROJECT_SOURCE_DIR}/src/LittlevGL/lv_drivers/display/SSD1963.c")
list(APPEND littlevGL_Sources "${PROJECT_SOURCE_DIR}/src/LittlevGL/lv_drivers/display/ST7565.c")
list(APPEND littlevGL_Sources "${PROJECT_SOURCE_DIR}/src/LittlevGL/lv_drivers/indev/AD_touch.c")
list(APPEND littlevGL_Sources "${PROJECT_SOURCE_DIR}/src/LittlevGL/lv_drivers/indev/evdev.c")
list(APPEND littlevGL_Sources "${PROJECT_SOURCE_DIR}/src/LittlevGL/lv_drivers/indev/FT5406EE8.c")
list(APPEND littlevGL_Sources "${PROJECT_SOURCE_DIR}/src/LittlevGL/lv_drivers/indev/keyboard.c")
list(APPEND littlevGL_Sources "${PROJECT_SOURCE_DIR}/src/LittlevGL/lv_drivers/indev/mouse.c")
list(APPEND littlevGL_Sources "${PROJECT_SOURCE_DIR}/src/LittlevGL/lv_drivers/indev/mousewheel.c")
list(APPEND littlevGL_Sources "${PROJECT_SOURCE_DIR}/src/LittlevGL/lv_drivers/indev/XPT2046.c")

list(APPEND littlevGL_Includes "${PROJECT_SOURCE_DIR}/src/LittlevGL/lvgl")
list(APPEND littlevGL_Includes "${PROJECT_SOURCE_DIR}/src/LittlevGL/lvgl/lv_core")
list(APPEND littlevGL_Includes "${PROJECT_SOURCE_DIR}/src/LittlevGL/lvgl/lv_draw")
list(APPEND littlevGL_Includes "${PROJECT_SOURCE_DIR}/src/LittlevGL/lvgl/lv_fonts")
list(APPEND littlevGL_Includes "${PROJECT_SOURCE_DIR}/src/LittlevGL/lvgl/lv_hal")
list(APPEND littlevGL_Includes "${PROJECT_SOURCE_DIR}/src/LittlevGL/lvgl/lv_misc")
list(APPEND littlevGL_Includes "${PROJECT_SOURCE_DIR}/src/LittlevGL/lvgl/lv_objx")
list(APPEND littlevGL_Includes "${PROJECT_SOURCE_DIR}/src/LittlevGL/lvgl/lv_porting")
list(APPEND littlevGL_Includes "${PROJECT_SOURCE_DIR}/src/LittlevGL/lvgl/lv_themes")

list(APPEND littlevGL_Includes "${PROJECT_SOURCE_DIR}/src/LittlevGL/lv_drivers/display")
list(APPEND littlevGL_Includes "${PROJECT_SOURCE_DIR}/src/LittlevGL/lv_drivers/indev")


# Display and touch drivers (nanoframework Community)
#__________________


list(APPEND littlevGL_Sources "${PROJECT_SOURCE_DIR}/src/LittlevGL/nfCommunityDrivers/ili9341_xpt2046/ili9341.c")
list(APPEND littlevGL_Sources "${PROJECT_SOURCE_DIR}/src/LittlevGL/nfCommunityDrivers/ili9341_xpt2046/xpt2046.c")
list(APPEND littlevGL_Sources "${PROJECT_SOURCE_DIR}/src/LittlevGL/nfCommunityDrivers/misc/disp_spi.c")
list(APPEND littlevGL_Sources "${PROJECT_SOURCE_DIR}/src/LittlevGL/nfCommunityDrivers/misc/tp_spi.c")


list(APPEND littlevGL_Includes "${PROJECT_SOURCE_DIR}/src/LittlevGL/nfCommunityDrivers/ili9341_xpt2046")
list(APPEND littlevGL_Includes "${PROJECT_SOURCE_DIR}/src/LittlevGL/nfCommunityDrivers/misc")

# make var global
#__________________
set(littlevGL_Sources ${littlevGL_Sources} CACHE INTERNAL "make global")
set(littlevGL_Includes ${littlevGL_Includes} CACHE INTERNAL "make global")






















































# make var global
set(littlevGL_Sources ${littlevGL_Sources} CACHE INTERNAL "make global")


