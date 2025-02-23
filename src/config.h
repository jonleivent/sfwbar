#ifndef __CONFIG_H__
#define __CONFIG_H__

#include <gtk/gtk.h>
#include "action.h"

enum ConfigSequenceType {
  SEQ_OPT,
  SEQ_CON,
  SEQ_REQ,
  SEQ_END
};

typedef gboolean (*parse_func) ( GScanner *, void * );

gchar *config_value_string ( gchar *dest, gchar *string );
GtkWidget *config_parse ( gchar *, gboolean );
void config_pipe_read ( gchar *command );
void config_string ( gchar *string );
gboolean config_expect_token ( GScanner *scan, gint token, gchar *fmt, ...);
void config_optional_semicolon ( GScanner *scanner );
void config_parse_sequence ( GScanner *scanner, ... );
gboolean config_assign_boolean (GScanner *scanner, gboolean def, gchar *expr);
gchar *config_assign_string ( GScanner *scanner, gchar *expr );
gdouble config_assign_number ( GScanner *scanner, gchar *expr );
gint config_assign_tokens ( GScanner *scanner, gchar *, gchar *, ... );
action_t *config_action ( GScanner *scanner );
void config_action_finish ( GScanner *scanner );
gchar *config_get_value ( GScanner *, gchar *, gboolean, gchar **);
void config_scanner ( GScanner *scanner );
void config_layout ( GScanner *, GtkWidget **, gboolean );
GtkWidget *config_include ( GScanner *scanner, gboolean toplevel );
void config_switcher ( GScanner *scanner );
void config_placer ( GScanner *scanner );
void config_popup ( GScanner *scanner );
GtkWidget *config_parse_toplevel ( GScanner *scanner, gboolean toplevel );

enum {
  G_TOKEN_SCANNER = G_TOKEN_LAST + 50,
  G_TOKEN_LAYOUT,
  G_TOKEN_POPUP,
  G_TOKEN_PLACER,
  G_TOKEN_SWITCHER,
  G_TOKEN_DEFINE,
  G_TOKEN_TRIGGERACTION,
  G_TOKEN_MAPAPPID,
  G_TOKEN_FILTERAPPID,
  G_TOKEN_FILTERTITLE,
  G_TOKEN_MODULE,
  G_TOKEN_THEME,
  G_TOKEN_DISOWNMINIMIZED,
  G_TOKEN_END,
  G_TOKEN_FILE,
  G_TOKEN_EXEC,
  G_TOKEN_MPDCLIENT,
  G_TOKEN_SWAYCLIENT,
  G_TOKEN_EXECCLIENT,
  G_TOKEN_SOCKETCLIENT,
  G_TOKEN_NUMBERW,
  G_TOKEN_STRINGW,
  G_TOKEN_NOGLOB,
  G_TOKEN_CHTIME,
  G_TOKEN_SUM,
  G_TOKEN_PRODUCT,
  G_TOKEN_LASTW,
  G_TOKEN_FIRST,
  G_TOKEN_GRID,
  G_TOKEN_SCALE,
  G_TOKEN_LABEL,
  G_TOKEN_BUTTON,
  G_TOKEN_IMAGE,
  G_TOKEN_CHART,
  G_TOKEN_INCLUDE,
  G_TOKEN_TASKBAR,
  G_TOKEN_PAGER,
  G_TOKEN_TRAY,
  G_TOKEN_STYLE,
  G_TOKEN_CSS,
  G_TOKEN_INTERVAL,
  G_TOKEN_VALUE,
  G_TOKEN_PINS,
  G_TOKEN_PREVIEW,
  G_TOKEN_COLS,
  G_TOKEN_ROWS,
  G_TOKEN_ACTION,
  G_TOKEN_DISPLAY,
  G_TOKEN_ICONS,
  G_TOKEN_LABELS,
  G_TOKEN_LOC,
  G_TOKEN_NUMERIC,
  G_TOKEN_PEROUTPUT,
  G_TOKEN_TITLEWIDTH,
  G_TOKEN_TOOLTIP,
  G_TOKEN_TRIGGER,
  G_TOKEN_GROUP,
  G_TOKEN_XSTEP,
  G_TOKEN_YSTEP,
  G_TOKEN_XORIGIN,
  G_TOKEN_YORIGIN,
  G_TOKEN_CHILDREN,
  G_TOKEN_SORT,
  G_TOKEN_FILTER,
  G_TOKEN_PRIMARY,
  G_TOKEN_TRUE,
  G_TOKEN_FALSE,
  G_TOKEN_MENU,
  G_TOKEN_AUTOCLOSE,
  G_TOKEN_MENUCLEAR,
  G_TOKEN_FUNCTION,
  G_TOKEN_USERSTATE,
  G_TOKEN_USERSTATE2,
  G_TOKEN_CLIENTSEND,
  G_TOKEN_ITEM,
  G_TOKEN_SEPARATOR,
  G_TOKEN_SUBMENU,
  G_TOKEN_MAXIMIZED,
  G_TOKEN_MINIMIZED,
  G_TOKEN_FULLSCREEN,
  G_TOKEN_FOCUSED,
  G_TOKEN_REGEX,
  G_TOKEN_JSON,
  G_TOKEN_SET,
  G_TOKEN_GRAB,
  G_TOKEN_TITLE,
  G_TOKEN_APPID,
  G_TOKEN_WORKSPACE,
  G_TOKEN_OUTPUT,
  G_TOKEN_FLOATING,
  G_TOKEN_INIT,
  G_TOKEN_LEFT,
  G_TOKEN_MIDDLE,
  G_TOKEN_RIGHT,
  G_TOKEN_SCROLL_UP,
  G_TOKEN_SCROLL_LEFT,
  G_TOKEN_SCROLL_RIGHT,
  G_TOKEN_SCROLL_DOWN,
  G_TOKEN_SHIFT,
  G_TOKEN_CTRL,
  G_TOKEN_MOD1,
  G_TOKEN_MOD2,
  G_TOKEN_MOD3,
  G_TOKEN_MOD4,
  G_TOKEN_MOD5,
  G_TOKEN_SUPER,
  G_TOKEN_HYPER,
  G_TOKEN_META
};

#endif
