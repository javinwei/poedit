/*
 *  This file is part of Poedit (http://www.poedit.net)
 *
 *  Copyright (C) 2000-2007 Vaclav Slavik
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a
 *  copy of this software and associated documentation files (the "Software"),
 *  to deal in the Software without restriction, including without limitation
 *  the rights to use, copy, modify, merge, publish, distribute, sublicense,
 *  and/or sell copies of the Software, and to permit persons to whom the
 *  Software is furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in
 *  all copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 *  DEALINGS IN THE SOFTWARE.
 *
 */

#include <wx/wxprec.h>

#include <wx/xrc/xmlres.h>
#include <wx/config.h>
#include <wx/listbox.h>
#include <wx/stattext.h>
#include <wx/intl.h>

#include "summarydlg.h"


MergeSummaryDialog::MergeSummaryDialog(wxWindow *parent)
{
    wxXmlResource::Get()->LoadDialog(this, parent, _T("summary"));
    wxSize sz(wxConfig::Get()->Read(_T("summary_pos_w"), -1),
              wxConfig::Get()->Read(_T("summary_pos_h"), -1));

    if (sz.x != -1)
        SetClientSize(sz);

    CentreOnParent();
}



MergeSummaryDialog::~MergeSummaryDialog()
{
    wxConfig::Get()->Write(_T("summary_pos_w"), (long)GetClientSize().x);
    wxConfig::Get()->Write(_T("summary_pos_h"), (long)GetClientSize().y);
}



void MergeSummaryDialog::TransferTo(const wxArrayString& snew, const wxArrayString& sobsolete)
{
    wxString sum;
    sum.Printf(_("(%i new, %i obsolete)"), 
               snew.GetCount(), sobsolete.GetCount());
    XRCCTRL(*this, "items_count", wxStaticText)->SetLabel(sum);

    wxListBox *listbox;
    size_t i;
    
    listbox = XRCCTRL(*this, "new_strings", wxListBox);
    for (i = 0; i < snew.GetCount(); i++)
    {
        listbox->Append(snew[i]);
    }

    listbox = XRCCTRL(*this, "obsolete_strings", wxListBox);
    for (i = 0; i < sobsolete.GetCount(); i++)
    {
        listbox->Append(sobsolete[i]);
    }
}
