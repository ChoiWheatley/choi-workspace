/*
 * << FLTK >> Designing a Simple Text Editor
 * source link : https://www.fltk.org/doc-1.3/editor.html
 * 
 * Achievements 
 *      1. Provide a menubar/menus for all functions
 *      2. Edit a single text file, possibly with multiple views.
 *      3. Load from a file.
 *      4. Save to a file.
 *      5. Cut/copy/delete/paste functions.
 *      6. Search and replace functions
 *      7. Keeo track of when the file has been changed
 * 
 * How To Compile it?
 *      1. install fltk from github (https://github.com/fltk/fltk)
 *      2. "fltk-config --compile $(your-project-name)"
 *      3. if not, "g++ -I/usr/local/include $(your-project-name) `fltk-config --ldflags`"
 * 
 * Author : Choi Wheatley
 * Last Edit : 2021. 01. 17
 * 
 */
#include "fltk-text-editor.h"
#include <iostream>

int main(int argc, char **argv) {
    textbuf = new Fl_Text_Buffer;
    EditorWindow* window = newview();
    window->show(1, argv);
    if (argc > 1) load_file(argv[1], -1);
    return Fl::run();
}

EditorWindow* newview() {
    static EditorWindow ret(640, 400);
    static Fl_Menu_Bar m(0, 0, 640, 30);
    m.copy(menuitems);
    // So that we can keep track of changes to the file, 
    // we also want to add a "modify" callback
    textbuf->add_modify_callback(changed_cb, &ret);
    textbuf->call_modify_callbacks();
    // To keep things simple our text editor will use the
    //          Fl_Text_Editor
    // widget to edit the text
    ret.editor = new Fl_Text_Editor(0, 30, 640, 370);
    ret.editor->buffer(textbuf);
    ret.editor->textfont(FL_COURIER);

    ret.add(m);
    ret.add(ret.editor);
    ret.resizable();

    strcpy(ret.search, "sample");

    return &ret;
}
EditorWindow::EditorWindow(int w_, int h_, const char * title_) : 
    Fl_Double_Window(w_, h_, title_)
{
    replace_dlg = new Fl_Window(300, 105, "Replace");
    replace_find = new Fl_Input(70, 10, 200, 25, "Find:");
    replace_with = new Fl_Input(70, 40, 200, 25, "Replace:");
    replace_all = new Fl_Button(10, 70, 90, 25, "Replace All");
    replace_next = new Fl_Return_Button(105, 70, 120, 25, "Replace Next");
    replace_cancel = new Fl_Button(230, 70, 60, 25, "Cancel");
    strcpy(filename, title_);
}
EditorWindow::~EditorWindow() {
    delete replace_dlg;
    delete replace_find;
    delete replace_with;
    delete replace_all;
    delete replace_next;
    delete replace_cancel;
    delete editor;
    free(search);
}

void changed_cb(int pos, int nInserted, int nDeleted,
                int nRestyled, const char* deletedText,
                void* cbArg) {
    if ((nInserted || nDeleted) && !loading) changed = 1;
    EditorWindow *w = (EditorWindow *) cbArg;
    set_title(w);
    if (loading) w->editor->show_insert_position();
}
// This callback function will clear the editor widget and current filename.
// It also calls the
//          check_save()
// function to give the user the opportunity to save the current file first 
// as needed.
void new_cb(Fl_Widget *, void *) {
    if (!check_save()) return;

    filename[0] = '\0';
    textbuf->select(0, textbuf->length());
    textbuf->remove_selection();
    changed = 0;
    textbuf->call_modify_callbacks();
}
// This callback function will ask the user for a filename and then load the specified
// file into the input widget and current filename. It also calls
//          check_save()
// function to give the user the opportunity to save the current file as needed.
// We call the
//          load_file()
// function to actually load the file.
void open_cb(Fl_Widget *, void *) {
    if (!check_save()) return;

    char *newfile = fl_file_chooser("Open File?", "*", filename);
    if (newfile != NULL) load_file(newfile, -1);
}
// void insert_cb(Fl_Widget *, void *);
// This callback saves the current file. If the current filename is blank
// it calls the "save as" callback
void save_cb(void) {
    if (filename[0] == '\0') {
        // No filename -- get one
        saveas_cb();
        return;
    }
    else save_file(filename);
}
// This callback asks the user for a filename and saves the current file
void saveas_cb(void) {
    char *newfile;

    newfile = fl_file_chooser("Save File As?", "*", filename);
    if (newfile != NULL) save_file(newfile);
}
// void view_cb(Fl_Widget *, void *);
// void close_cb(Fl_Widget *, void *);
// The quit callback will first see if the current file has been modified.
// and if so give the user a chance to save it. It then exits from the
// program.
void quit_cb(Fl_Widget *, void *) {
    if (changed && !check_save()) return;
    exit(0);
}
//void undo_cb(Fl_Widget *, void *);

// this callback function will call 
//          Fl_Text_Editor::kf_cut() 
// to cut the currently selected text to the clipboard
void cut_cb(Fl_Widget *, void * v) {
    // DEBUG
    std::cout << "DBG : cut_cb() function called\n";
    EditorWindow *e = (EditorWindow *)v;
    Fl_Text_Editor::kf_cut(0, e->editor);
}
// This callback function will call 
//          Fl_Text_Editor::kf_copy() 
// to copy the currently selected text to the clipboard
//          kf_copy(int c, Fl_Text_Editor* e)
//      Does a copy of selected
//      text or the current character in the current buffer of 
//      editor 'e'
void copy_cb(Fl_Widget *, void * v) {
    // DEBUG
    std::cout << "DBG : copy_cb() function called\n";
    EditorWindow * e = (EditorWindow *)v;
    Fl_Text_Editor::kf_copy(0, e->editor);
}
// This callback function will call
//           Fl_Text_Editor::kf_paste()
// to paste the clipboard at the current position
void paste_cb(Fl_Widget *, void * v) {
    EditorWindow *e = (EditorWindow *)v;
    Fl_Text_Editor::kf_paste(0, e->editor);
}
// This callback function will call 
//          Fl_Text_Buffer::remove_selection()
// to delete the currently selected text to the clipboard
void delete_cb(Fl_Widget *, void *) {
    textbuf->remove_selection();
}
// This callback function asks for a search string using the
//          fl_input()          // which have to be included <FL/fl_ask.H>
// convenience function which shows an input dialog displaying the fmt message
// and then calls the 
//          find2_cb()
// function to find the string 
void find_cb(Fl_Widget * w, void * v) {
    EditorWindow *e = (EditorWindow *) v;
    const char * val = fl_input("Search String:");
    if (val != NULL) {
        // User entered a string -- go and find it!
        strcpy(e->search, val);
        // DEBUG
        std::cout << "DBG : function \'find_cb()\' entered\n";
        std::cout << "\tsearch= " << e->search << '\n';
        find2_cb(w, v);
    }
}
// This function will find the next occurence of the search string.
// If the search string is blank then we want to pop up the search
// dialog:
void find2_cb(Fl_Widget * w, void * v) {
    EditorWindow* e = (EditorWindow *) v;
    if (e->search[0] == '\0') {
        // Search string is blank! get a new one...
        find_cb(w, v);
        return;
    }

    int pos = e->editor->insert_position();
    int found = textbuf->search_forward(pos, e->search, &pos);
    if (found) {
        // Found a match; select and update the position...
        textbuf->select(pos, pos+strlen(e->search));
        e->editor->insert_position(pos+strlen(e->search));
        e->editor->show_insert_position();
    }
    // If the search string cannot be found we use the 
    //          fl_alert()
    // convenience function to display a message to that effect
    else fl_alert("No occurrences of \'%s\' found!!", e->search);
}
// The replace callback just shows the replace dialog
void replace_cb(Fl_Widget *, void * v) {
    EditorWindow *e = (EditorWindow *)v;
    e->replace_dlg->show();
}
// This callback will replace the next occurence of the replacement string.
// It nothing has been entered for the replacement string,
// then the replace dialog is displayed instead
void replace2_cb(Fl_Widget *, void * v) {
    EditorWindow *e = (EditorWindow *)v;
    const char *find = e->replace_find->value();
    const char *replace = e->replace_with->value();
    if (find[0] == '\0') {
        // Search string is blank; get a new one...
        e->replace_dlg->show();
        return;
    }

    e->replace_dlg->hide();

    int pos = e->editor->insert_position();
    int found = textbuf->search_forward(pos, find, &pos);

    if (found) {
        // Found a match; update the position and replace text...
        textbuf->select(pos, pos+strlen(find));
        textbuf->remove_selection();
        textbuf->insert(pos, replace);
        textbuf->select(pos, pos+strlen(replace));
        e->editor->insert_position(pos+strlen(replace));
        e->editor->show_insert_position();
    }
    else fl_alert("No occurrences of \'%s\' found!", find);
}
// This callback will replace all occurrences of the search string in the file
void replall_cb(Fl_Widget *, void* v) {
    EditorWindow* e = (EditorWindow *)v;
    const char *find = e->replace_find->value();
    const char *replace = e->replace_with->value();

    if (find[0] == '\0') {
        // Search string is blank; get a new one...
        e->replace_dlg->show();
        return;
    }

    e->replace_dlg->hide();

    e->editor->insert_position(0);
    int times = 0;

    // Loop through the whole string
    for (int found = 1; found; ) {
        int pos = e->editor->insert_position();
        found = textbuf->search_forward(pos, find, &pos);

        if (found) {
            // Found a match; update the position and replace text...
            textbuf->select(pos, pos + strlen(find));
            textbuf->remove_selection();
            textbuf->insert(pos, replace);
            e->editor->insert_position(pos+strlen(replace));
            e->editor->show_insert_position();
            times++;
        }
    }
    if (times) fl_message("Replaced %d occurrences.", times);
    else fl_alert("No occurrences of \'%s\' found!", find);
}
// This callback just hides the replace dialog
void replcan_cb(Fl_Widget *, void* v) {
    EditorWindow * e = (EditorWindow *)v;
    e->replace_dlg->hide();
}
// This function checks to see if the current file needs to be saved.
// If so, asks the user if they want to save it
int check_save(void) {
    if (!changed) return 1;

    int r = fl_choice("The current file has not been saved.\n"
                        "Would you like to save it now?",
                        "Cancel", "Save", "Discard");
    if (r == 1) {
        save_cb();      //save the file
        return !changed;
    }
    return (r == 2) ? 1 : 0;
}
// This function checks the $(changed) variable and updates the window label accordingly
void set_title(EditorWindow* w) {
    static char title[256] = "Hello World";
    if (filename[0] == '\0') strcpy(title, "Untitled");
    else {
        char *slash;
        slash = strrchr(filename, '/');
    #ifdef WIN32
        if (slash == NULL) slash = strrchr(filename, '\\');
    #endif
        if (slash != NULL) strcpy(title, slash+1);
        else strcpy(title, filename);

    }
    if (changed) strcat(title, " (modified)");

    w->label(title);
}
// This function loads the specified file into the textbuf variable
void load_file(char *newfile, int ipos) {
    loading = 1;
    int insert = (ipos != -1);
    changed = insert;
    if (!insert) strcpy(filename, "");
    int r;
    if (!insert) r = textbuf->loadfile(newfile);
    else  r = textbuf->insertfile(newfile, ipos);
    if (r) 
        fl_alert("Error reading from file \'%s\':\n%s.", newfile, strerror(errno));
    else
        if(!insert) strcpy(filename, newfile);
    loading = 0;
    textbuf->call_modify_callbacks();
}
// This function saves the current buffer to the specitied file
void save_file(char *newfile) {
    if (textbuf->savefile(newfile))
        fl_alert("Error writing to file \'%s\':\n%s.", newfile, strerror(errno));
    else
        strcpy(filename, newfile);
    changed = 0;
    textbuf->call_modify_callbacks();
}