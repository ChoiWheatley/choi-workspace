#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Repeat_Button.H>
#include <FL/Fl_Return_Button.H>
#include <FL/Fl_Text_Editor.H>
#include <FL/Fl_Menu_Item.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/fl_ask.H>
#include <FL/Fl_File_Chooser.H>
#include <cstring>
#include <errno.h>

class EditorWindow : public Fl_Double_Window {
    public:
        EditorWindow(int w, int h, const char* t);
        ~EditorWindow();

        Fl_Window           *replace_dlg;
        Fl_Input            *replace_find;
        Fl_Input            *replace_with;
        Fl_Button           *replace_all;
        Fl_Return_Button    *replace_next;
        Fl_Button           *replace_cancel;

        Fl_Text_Editor      *editor;
        char                search[256];
};

// Global Variables
int             changed = 0;
int             loading = 0;
char            filename[256] = "";
char*           title;
Fl_Text_Buffer  *textbuf;

// Global functions
EditorWindow* newview();
void new_cb(Fl_Widget *, void *);
void open_cb(Fl_Widget *, void *);
//void insert_cb(Fl_Widget *, void *);
void save_cb(void);
void saveas_cb(void);
//void view_cb(Fl_Widget *, void *);
//void close_cb(Fl_Widget *, void *);
void quit_cb(Fl_Widget *, void *);
//void undo_cb(Fl_Widget *, void *);
void cut_cb(Fl_Widget *, void *);
void copy_cb(Fl_Widget *, void *);
void paste_cb(Fl_Widget *, void *);
void delete_cb(Fl_Widget *, void *);
void find_cb(Fl_Widget *, void *);
void find2_cb(Fl_Widget *, void *);
void replace_cb(Fl_Widget *, void *);
void replace2_cb(Fl_Widget *, void *);
void replall_cb(Fl_Widget *, void*);
void replcan_cb(Fl_Widget *, void*);
void changed_cb(int pos, int nInserted, int nDeleted,
                int nRestyled, const char* deletedText,
                void* cbArg);
void set_title(EditorWindow*);
int check_save(void);
void load_file(char *newfile, int ipos);
void save_file(char *newfile);

// Menubars and Menus
// The first goal requires us to use a menubar and menus that define each function the editor needs 
// to perform. we will define the callback functions(new_cb, ...) later 
// Once we have the menus defined we can create the Fl_Menu_Bar widget and assign the menus to it with:
//      Fl_Menu_Bar *m = new Fl_Menu_bar(0, 0, 640, 30);
//      m->copy(menuitems);
Fl_Menu_Item menuitems[] = {
    { "&File",              0, 0, 0, FL_SUBMENU },
        { "&New File",          0, (Fl_Callback *)new_cb },
        { "&Open File...",      FL_COMMAND + 'o', (Fl_Callback *)open_cb },
        //{ "&Insert File...",    FL_COMMAND + 'i', (Fl_Callback *)insert_cb, 0, FL_MENU_DIVIDER },
        { "&Save File",         FL_COMMAND + 's', (Fl_Callback *)save_cb },
        { "Save File &As...",   FL_COMMAND + FL_SHIFT + 's', (Fl_Callback *)saveas_cb, 0, FL_MENU_DIVIDER },
        //{ "New &View",          FL_ALT + 'v', (Fl_Callback *)view_cb, 0 },
        //{ "&Close View",        FL_COMMAND + 'w', (Fl_Callback *)close_cb, 0, FL_MENU_DIVIDER },
        { "E&xit",              FL_COMMAND + 'q', (Fl_Callback *)quit_cb, 0 },
        { 0 },
    
    { "&Edit", 0, 0, 0, FL_SUBMENU },
        //{ "&Undo",              FL_COMMAND + 'z', (Fl_Callback *)undo_cb, 0, FL_MENU_DIVIDER },
        { "Cu&t",               FL_COMMAND + 'x', (Fl_Callback *)cut_cb },
        { "&Copy",              FL_COMMAND + 'c', (Fl_Callback *)copy_cb },
        { "&Paste",             FL_COMMAND + 'v', (Fl_Callback *)paste_cb },
        { "&Delete",            0, (Fl_Callback *)delete_cb },
        { 0 },

    { "&Search", 0, 0, 0, FL_SUBMENU },
        { "&Find...",           FL_COMMAND + 'f', (Fl_Callback *)find_cb },
        { "F&ind Again",        FL_COMMAND + 'g', find2_cb },
        { "&Replace...",        FL_COMMAND + 'r', replace_cb },
        { "Re&place Again",     FL_COMMAND + 't', replace2_cb },
        { 0 },
    
    { 0 },
};
