/* gEDA - GPL Electronic Design Automation
 * gschem - gEDA Schematic Capture
 * Copyright (C) 1998-2000 Ales V. Hvezda
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111 USA
 */
#include <config.h>

#include <stdio.h>
#include <sys/stat.h>
#include <ctype.h>
#ifdef HAVE_STRING_H
#include <string.h>
#endif
#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif
#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif

#include <libgeda/libgeda.h>

#include "../include/globals.h"
#include "../include/prototype.h"

#ifdef HAVE_LIBDMALLOC
#include <dmalloc.h>
#endif

/*! \todo Finish function documentation!!!
 *  \brief
 *  \par Function Description
 *
 */
void set_window_current_key(TOPLEVEL *w_current)
{
       /*window_current = w_current;*/
       /* this function is now a nop, remove it */
}

/*! \todo Finish function documentation!!!
 *  \brief
 *  \par Function Description
 *
 */
/* for now this only supports single chars, not shift/alt/ctrl etc... */
void g_keys_execute(int state, int keyval)
{
  char *guile_string = NULL;
  char *modifier = NULL;

  if (keyval == 0) {
    return;
  }

  /* don't pass the raw modifier key presses to the guile code */
  if (strstr(gdk_keyval_name(keyval), "Alt")) {
    return;
  }

  if (strstr(gdk_keyval_name(keyval), "Shift")) {
    return;
  }

  if (strstr(gdk_keyval_name(keyval), "Control")) {
    return;
  }

  if (state & GDK_SHIFT_MASK) {
    modifier = g_strdup_printf("\"Shift ");
  } else if (state & GDK_CONTROL_MASK) {
    modifier = g_strdup_printf("\"Control ");
  } else if (state & GDK_MOD1_MASK) {
    modifier = g_strdup_printf("\"Alt ");
  } else {
    modifier = g_strdup_printf("\"");
  }

  guile_string = g_strdup_printf("(press-key %s%s\")",
				 modifier, gdk_keyval_name (keyval));

#if DEBUG 
  printf("_%s_\n", guile_string);
#endif
  scm_c_eval_string (guile_string);
  g_free(guile_string);
  g_free(modifier);

#if 0 /* playing with thi's guile stuff */
  gh_eval_str("(display (reverse last-command-sequence))");
  printf("\n");
#endif
}

/*! \brief
 *
 */
#define DEFINE_G_KEYS(name)				\
SCM g_keys_ ## name(void)				\
{							\
	i_callback_ ## name(global_window_current, 0, NULL);	\
	return SCM_BOOL_T;				\
}

/*! \brief test-comment
 * test-comment
 */
DEFINE_G_KEYS(file_new)

DEFINE_G_KEYS(file_new_window)

/* don't use the widget parameter on this function, or do some checking... */
/* since there is a call: widget = NULL, data = 0 (will be w_current) */
/* This should be renamed to page_open perhaps... */
DEFINE_G_KEYS(file_open)

/* don't use the widget parameter on this function, or do some checking... */
/* since there is a call: widget = NULL, data = 0 (will be w_current) */
DEFINE_G_KEYS(file_script)

/* don't use the widget parameter on this function, or do some checking... */
/* since there is a call: widget = NULL, data = 0 (will be w_current) */
DEFINE_G_KEYS(file_save)
DEFINE_G_KEYS(file_save_as)
DEFINE_G_KEYS(file_save_all)
DEFINE_G_KEYS(file_print)
DEFINE_G_KEYS(file_write_png)

/* don't use the widget parameter on this function, or do some checking... */
/* since there is a call: widget = NULL, data = 0 (will be w_current) */
/* this function closes a window */
DEFINE_G_KEYS(file_close)
DEFINE_G_KEYS(file_quit)

/* Select also does not update the middle button shortcut */
DEFINE_G_KEYS(edit_undo)
DEFINE_G_KEYS(edit_redo)
DEFINE_G_KEYS(edit_select)
DEFINE_G_KEYS(edit_copy)
DEFINE_G_KEYS(edit_copy_hotkey)
DEFINE_G_KEYS(edit_mcopy)
DEFINE_G_KEYS(edit_mcopy_hotkey)
DEFINE_G_KEYS(edit_move)
DEFINE_G_KEYS(edit_move_hotkey)
DEFINE_G_KEYS(edit_delete)
DEFINE_G_KEYS(edit_rotate_90)
DEFINE_G_KEYS(edit_rotate_90_hotkey)
DEFINE_G_KEYS(edit_mirror)
DEFINE_G_KEYS(edit_mirror_hotkey)
#if 0 /* obsolete */
DEFINE_G_KEYS(edit_stretch)
DEFINE_G_KEYS(edit_stretch_hotkey)
#endif
DEFINE_G_KEYS(edit_slot)
DEFINE_G_KEYS(edit_color)
DEFINE_G_KEYS(edit_edit)
DEFINE_G_KEYS(edit_text)
DEFINE_G_KEYS(edit_lock)
DEFINE_G_KEYS(edit_unlock)
DEFINE_G_KEYS(edit_linetype)
DEFINE_G_KEYS(edit_filltype)
DEFINE_G_KEYS(edit_translate)
DEFINE_G_KEYS(edit_embed)
DEFINE_G_KEYS(edit_unembed)
DEFINE_G_KEYS(edit_update)
DEFINE_G_KEYS(edit_show_hidden)
DEFINE_G_KEYS(edit_make_visible)
DEFINE_G_KEYS(edit_find)
DEFINE_G_KEYS(edit_show_text)
DEFINE_G_KEYS(edit_hide_text)
DEFINE_G_KEYS(edit_autonumber_text)

DEFINE_G_KEYS(buffer_copy1)
DEFINE_G_KEYS(buffer_copy2)
DEFINE_G_KEYS(buffer_copy3)
DEFINE_G_KEYS(buffer_copy4)
DEFINE_G_KEYS(buffer_copy5)
DEFINE_G_KEYS(buffer_cut1)
DEFINE_G_KEYS(buffer_cut2)
DEFINE_G_KEYS(buffer_cut3)
DEFINE_G_KEYS(buffer_cut4)
DEFINE_G_KEYS(buffer_cut5)
DEFINE_G_KEYS(buffer_paste1)
DEFINE_G_KEYS(buffer_paste2)
DEFINE_G_KEYS(buffer_paste3)
DEFINE_G_KEYS(buffer_paste4)
DEFINE_G_KEYS(buffer_paste5)
DEFINE_G_KEYS(buffer_paste1_hotkey)
DEFINE_G_KEYS(buffer_paste2_hotkey)
DEFINE_G_KEYS(buffer_paste3_hotkey)
DEFINE_G_KEYS(buffer_paste4_hotkey)
DEFINE_G_KEYS(buffer_paste5_hotkey)

/* repeat middle shortcut doesn't make sense on redraw, just hit right
 * button */
DEFINE_G_KEYS(view_redraw)

/* for these functions, repeat middle shortcut would get into the way
 * of what user is try to do */
DEFINE_G_KEYS(view_zoom_full)
DEFINE_G_KEYS(view_zoom_extents)
DEFINE_G_KEYS(view_zoom_in)
DEFINE_G_KEYS(view_zoom_out)
DEFINE_G_KEYS(view_zoom_in_hotkey)
DEFINE_G_KEYS(view_zoom_out_hotkey)

DEFINE_G_KEYS(view_zoom_box)
DEFINE_G_KEYS(view_zoom_box_hotkey)
DEFINE_G_KEYS(view_pan)
DEFINE_G_KEYS(view_pan_hotkey)
DEFINE_G_KEYS(view_update_cues)
DEFINE_G_KEYS(page_manager)
DEFINE_G_KEYS(page_next)
DEFINE_G_KEYS(page_prev)
DEFINE_G_KEYS(page_new)
DEFINE_G_KEYS(page_close)
DEFINE_G_KEYS(page_revert)
DEFINE_G_KEYS(page_discard)
DEFINE_G_KEYS(page_print)
DEFINE_G_KEYS(add_component)
DEFINE_G_KEYS(add_attribute)
DEFINE_G_KEYS(add_attribute_hotkey)
DEFINE_G_KEYS(add_net)
DEFINE_G_KEYS(add_net_hotkey)
DEFINE_G_KEYS(add_bus)
DEFINE_G_KEYS(add_bus_hotkey)
DEFINE_G_KEYS(add_text)
DEFINE_G_KEYS(add_line)
DEFINE_G_KEYS(add_line_hotkey)
DEFINE_G_KEYS(add_box)
DEFINE_G_KEYS(add_box_hotkey)
DEFINE_G_KEYS(add_picture)
DEFINE_G_KEYS(add_picture_hotkey)
DEFINE_G_KEYS(add_circle)
DEFINE_G_KEYS(add_circle_hotkey)
DEFINE_G_KEYS(add_arc)
DEFINE_G_KEYS(add_arc_hotkey)
DEFINE_G_KEYS(add_pin)
DEFINE_G_KEYS(add_pin_hotkey)
DEFINE_G_KEYS(hierarchy_down_schematic)
DEFINE_G_KEYS(hierarchy_down_symbol)
DEFINE_G_KEYS(hierarchy_up)
DEFINE_G_KEYS(hierarchy_documentation)
DEFINE_G_KEYS(attributes_attach)
DEFINE_G_KEYS(attributes_detach)
DEFINE_G_KEYS(attributes_show_name)
DEFINE_G_KEYS(attributes_show_value)
DEFINE_G_KEYS(attributes_show_both)
DEFINE_G_KEYS(attributes_visibility_toggle)

/* i_callback_script_console is not currently implemented */
DEFINE_G_KEYS(script_console)

/* repeat last command doesn't make sense on options either??? (does
 * it?) */
DEFINE_G_KEYS(options_text_size)

/* repeat last command doesn't make sense on options either??? (does
 * it?) */
DEFINE_G_KEYS(options_afeedback)
DEFINE_G_KEYS(options_grid)
DEFINE_G_KEYS(options_snap)
DEFINE_G_KEYS(options_snap_size)
DEFINE_G_KEYS(options_rubberband)
DEFINE_G_KEYS(options_show_log_window)
DEFINE_G_KEYS(options_show_coord_window)
DEFINE_G_KEYS(misc)
DEFINE_G_KEYS(misc2)
DEFINE_G_KEYS(misc3)

DEFINE_G_KEYS(help_about)
DEFINE_G_KEYS(help_manual)
DEFINE_G_KEYS(help_hotkeys)

/* be sure that you don't use the widget parameter in this one, since it is
being called with a null, I suppose we should call it with the right param.
hack */
DEFINE_G_KEYS(cancel)


/*! \todo Finish function documentation!!!
 *  \brief
 *  \par Function Description
 *
 */
/*help for generate-netlist hot key*/
SCM g_get_selected_filename(void)                     
{                                                     
	return (get_selected_filename(global_window_current));
}

/*! \todo Finish function documentation!!!
 *  \brief
 *  \par Function Description
 *
 */
SCM g_get_selected_component_attributes(void)                 
{
  return (get_selected_component_attributes(global_window_current));
}