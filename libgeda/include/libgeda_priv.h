/* System headers which libgeda headers rely on */
#include <glib.h>
#include <gtk/gtk.h> /* FIXME */
#include <libguile.h>
#include "guile_compat_1.6.h"

/* Public libgeda headers */
#include "defines.h"
#include "struct.h"
#include "globals.h"
#include "o_types.h"
#include "colors.h"
#include "i_vars.h"
#include "papersizes.h"
#include "prototype.h"
#include "funcs.h"

#include "geda_list.h"

/* Private libgeda headers */
#include "prototype_priv.h"

/* Dummy _() macro for future gettext translation FIXME */
#define _(X) X