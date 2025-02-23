/* This entire file is licensed under GNU General Public License v3.0
 *
 * Copyright 2022- sfwbar maintainers
 */

#include "sfwbar.h"
#include "pager.h"
#include "pageritem.h"

G_DEFINE_TYPE_WITH_CODE (PagerItem, pager_item, FLOW_ITEM_TYPE, G_ADD_PRIVATE (PagerItem));

void pager_item_update ( GtkWidget *self )
{
  PagerItemPrivate *priv;

  g_return_if_fail(IS_PAGER_ITEM(self));
  priv = pager_item_get_instance_private(PAGER_ITEM(self));

  if(!priv->invalid)
    return;

  if(g_strcmp0(gtk_button_get_label(GTK_BUTTON(priv->button)),priv->ws->name))
    gtk_button_set_label(GTK_BUTTON(priv->button),priv->ws->name);
  gtk_widget_set_has_tooltip(priv->button,
      GPOINTER_TO_INT(g_object_get_data(G_OBJECT(priv->pager),"preview")));
  if ( pager_workspace_is_focused(priv->ws) )
    gtk_widget_set_name(priv->button, "pager_focused");
  else if (priv->ws->visible)
    gtk_widget_set_name(priv->button, "pager_visible");
  else
    gtk_widget_set_name(priv->button, "pager_normal");

  gtk_widget_unset_state_flags(gtk_bin_get_child(GTK_BIN(self)),
      GTK_STATE_FLAG_PRELIGHT);

  flow_item_set_active(self, priv->ws->id != GINT_TO_POINTER(-1) ||
      g_list_find_custom(g_object_get_data(G_OBJECT(priv->pager),"pins"),
        priv->ws->name, (GCompareFunc)g_strcmp0)!=NULL);

  priv->invalid = FALSE;
}

workspace_t *pager_item_get_workspace ( GtkWidget *self )
{
  PagerItemPrivate *priv;

  g_return_val_if_fail(IS_PAGER_ITEM(self),NULL);
  priv = pager_item_get_instance_private(PAGER_ITEM(self));

  return priv->ws;
}

static void pager_item_invalidate ( GtkWidget *self )
{
  PagerItemPrivate *priv;

  if(!self)
    return;

  g_return_if_fail(IS_PAGER_ITEM(self));
  priv = pager_item_get_instance_private(PAGER_ITEM(self));

  flow_grid_invalidate(priv->pager);
  priv->invalid = TRUE;
}

static gint pager_item_compare ( GtkWidget *a, GtkWidget *b, GtkWidget *parent)
{
  PagerItemPrivate *p1,*p2;

  g_return_val_if_fail(IS_PAGER_ITEM(a),0);
  g_return_val_if_fail(IS_PAGER_ITEM(b),0);

  p1 = pager_item_get_instance_private(PAGER_ITEM(a));
  p2 = pager_item_get_instance_private(PAGER_ITEM(b));

  if(g_object_get_data(G_OBJECT(parent),"sort_numeric"))
    return strtoll(p1->ws->name, NULL, 10)-strtoll(p2->ws->name, NULL, 10);
  else
    return g_strcmp0(p1->ws->name, p2->ws->name);
}

static void pager_item_class_init ( PagerItemClass *kclass )
{
  FLOW_ITEM_CLASS(kclass)->update = pager_item_update;
  FLOW_ITEM_CLASS(kclass)->get_parent = (void * (*)(GtkWidget *))pager_item_get_workspace;
  FLOW_ITEM_CLASS(kclass)->compare = pager_item_compare;
  FLOW_ITEM_CLASS(kclass)->invalidate = pager_item_invalidate;
}

static void pager_item_init ( PagerItem *self )
{
}

static void pager_item_button_cb( GtkWidget *self, gpointer data )
{
  pager_set_workspace(data);
}

static gboolean pager_item_draw_preview ( GtkWidget *widget, cairo_t *cr,
    workspace_t *ws )
{
  GtkStyleContext *style;
  GdkRGBA fg;
  guint w,h,i,n;
  gint focus;
  GdkRectangle *wins, spc;

  w = gtk_widget_get_allocated_width (widget);
  h = gtk_widget_get_allocated_height (widget);
  style = gtk_widget_get_style_context(widget);
  gtk_style_context_get_color (style,GTK_STATE_FLAG_NORMAL, &fg);
  cairo_set_line_width(cr,1);

  n = pager_get_geom(ws,&wins,&spc,&focus);
  if(!n)
    return TRUE;
  for(i=0;i<n;i++)
  {
    if(i==focus)
      cairo_set_source_rgba(cr,fg.red,fg.blue,fg.green,1);
    else
      cairo_set_source_rgba(cr,fg.red,fg.blue,fg.green,0.5);
    cairo_rectangle(cr,
        (int)(wins[i].x*w/spc.width),
        (int)(wins[i].y*h/spc.height),
        (int)(wins[i].width*w/spc.width),
        (int)(wins[i].height*h/spc.height));
    cairo_fill(cr);
    gtk_render_frame(style,cr,
        (int)(wins[i].x*w/spc.width),
        (int)(wins[i].y*h/spc.height),
        (int)(wins[i].width*w/spc.width),
        (int)(wins[i].height*h/spc.height));
    cairo_stroke(cr);
  }
  g_free(wins);

  return TRUE;
}

static gboolean pager_item_draw_tooltip ( GtkWidget *widget, gint x, gint y,
    gboolean kbmode, GtkTooltip *tooltip, workspace_t *ws )
{
  GtkWidget *button;

  button = gtk_button_new();
  g_signal_connect(button,"draw",G_CALLBACK(pager_item_draw_preview),ws);
  gtk_widget_set_name(button, "pager_preview");
  gtk_tooltip_set_custom(tooltip,button);
  return TRUE;
}

GtkWidget *pager_item_new( GtkWidget *pager, workspace_t *ws )
{
  GtkWidget *self;
  PagerItemPrivate *priv;

  if(flow_grid_find_child(base_widget_get_child(pager),ws))
    return NULL;

  if(IS_BASE_WIDGET(pager))
    pager = base_widget_get_child(pager);

  self = GTK_WIDGET(g_object_new(pager_item_get_type(), NULL));
  priv = pager_item_get_instance_private(PAGER_ITEM(self));

  priv->ws = ws;
  priv->pager = pager;

  priv->button = gtk_button_new_with_label(ws->name);
  gtk_container_add(GTK_CONTAINER(self),priv->button);
  gtk_widget_set_name(priv->button, "pager_normal");
  g_signal_connect(priv->button,"clicked",G_CALLBACK(pager_item_button_cb),ws);
  g_signal_connect(priv->button,"query-tooltip",
      G_CALLBACK(pager_item_draw_tooltip),ws);
  g_object_ref(G_OBJECT(self));
  flow_grid_add_child(pager,self);
  pager_item_invalidate(self);

  return self;
}
