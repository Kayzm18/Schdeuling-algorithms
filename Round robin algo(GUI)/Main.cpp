/*
School of Information and Communication Technology
Course                  : CS 225 - OPERATING SYSTEMS
Lecture                 : Dr Ntalasha
Assignment              : 1
Scheduling Algorithm    : Round Robin
Group Members           :
 Full name             SIN
 ----------------------------------
Bwalya lemmy            23127135
Mwaba K Mwaba           23139345
Thabwela Dzekedzeke     23132747
Grace Kanchinyi         23132965
Kawana Mutanuka         23125084
*/

//libralies
#include <wx/wx.h>
#include <wx/grid.h>
#include <wx/tokenzr.h>
#include <vector>

class SchedulerFrame : public wxFrame {
public:
    SchedulerFrame() : wxFrame(NULL, wxID_ANY, "Round Robin Scheduler", wxDefaultPosition, wxSize(800, 600)) {
        wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

        // Getting User input
        wxBoxSizer* inputSizer = new wxBoxSizer(wxHORIZONTAL);
        inputSizer->Add(new wxStaticText(this, wxID_ANY, "Proceses: "), 0, wxALL | wxALIGN_CENTER_VERTICAL, 3);
        procCtrl = new wxTextCtrl(this, wxID_ANY);
        inputSizer->Add(procCtrl, 1, wxALL, 5);
        inputSizer->Add(new wxStaticText(this, wxID_ANY, "Burst-Times (separated by commas): "), 0, wxALL |wxALIGN_CENTER_VERTICAL, 5);
        burstCtrl = new wxTextCtrl(this, wxID_ANY);
        inputSizer->Add(burstCtrl, 2, wxALL, 5);
        inputSizer->Add(new wxStaticText(this, wxID_ANY, "Quantum: "), 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);
        quantumCtrl= new wxTextCtrl(this, wxID_ANY);
        inputSizer->Add(quantumCtrl, 1, wxALL, 5);
        wxButton* runBtn = new wxButton(this, wxID_ANY, "Run Scheduler");
        inputSizer->Add(runBtn, 0, wxALL,6);

        mainSizer->Add(inputSizer,0, wxEXPAND);

        // The Table
        grid = new wxGrid(this, wxID_ANY);
        grid->CreateGrid(0, 4);
        grid->SetColLabelValue(0, "Process");
        grid->SetColLabelValue(1, "Burst Time");
        grid->SetColLabelValue(2, "Turnaround Time");
        grid->SetColLabelValue(3, "Waiting Time");

        mainSizer->Add(grid, 1, wxEXPAND | wxALL, 5);

        drawPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(-1, 150));
        drawPanel->SetBackgroundStyle(wxBG_STYLE_PAINT);
        drawPanel->Bind(wxEVT_PAINT, &SchedulerFrame::OnPaint, this);

        mainSizer->Add(drawPanel, 0, wxEXPAND | wxALL, 5);
        SetSizer(mainSizer);
        runBtn->Bind(wxEVT_BUTTON, &SchedulerFrame::OnRunScheduler, this);
    }

private:
    wxTextCtrl *procCtrl, *burstCtrl, *quantumCtrl;
    wxGrid* grid;
    wxPanel* drawPanel;
    std::vector<int> burstTimes, turnAroundTimes, waitingTimes, schedule;

    void OnRunScheduler(wxCommandEvent&) {

        int n = wxAtoi(procCtrl->GetValue());
        int quantum = wxAtoi(quantumCtrl->GetValue());
        wxStringTokenizer tokenizer(burstCtrl->GetValue(), ",");
        burstTimes.clear();
        while (tokenizer.HasMoreTokens()) {
            burstTimes.push_back(wxAtoi(tokenizer.GetNextToken()));
        }

        if (n != burstTimes.size() || quantum <= 0) {
            wxMessageBox("Invalid input. Check number of processes, burst times, or quantum.", "Error", wxOK | wxICON_ERROR);
            return;
        }

        // Actuall RR CODE
        std::vector<int> rem_bt = burstTimes;
        turnAroundTimes.assign(n, 0);
        waitingTimes.assign(n, 0);
        schedule.clear();

        int sq = 0;
        while (true) {
            int count = 0;
            for (int i = 0; i < n; i++) {
                if (rem_bt[i] == 0) {
                    count++;
                    continue;
                }
                schedule.push_back(i);
                if (rem_bt[i] > quantum) {
                    rem_bt[i] -= quantum;
                    sq += quantum;
                } else {
                    sq += rem_bt[i];
                    turnAroundTimes[i] = sq;
                    rem_bt[i] = 0;
                }
            }
            if (count == n) break;
        }

        for (int i = 0; i < n; i++) {
            waitingTimes[i] = turnAroundTimes[i] - burstTimes[i];
        }
        //Ends here

        //Drawing the grid
        grid->ClearGrid();
        if (grid->GetNumberRows()> 0) grid->DeleteRows(0, grid->GetNumberRows());
        grid->AppendRows(n);
        for (int i = 0; i < n; i++) {
            grid->SetCellValue(i, 0, wxString::Format("P%d", i + 1));
            grid->SetCellValue(i,1, wxString::Format("%d", burstTimes[i]));
            grid->SetCellValue(i, 2, wxString::Format("%d", turnAroundTimes[i]));
            grid->SetCellValue(i, 3, wxString::Format("%d", waitingTimes[i]));
        }

        drawPanel->Refresh();
    }
    //Drawing of Gant Chart
    void OnPaint(wxPaintEvent&) {
        wxPaintDC dc(drawPanel);
        wxSize size = drawPanel->GetClientSize();
        int blockWidth= 50;
        int blockHeight = 30;
        int x = 10;
        int y = size.GetHeight()/ 2 - blockHeight / 2;

        for (int pid : schedule) {
            wxString label = wxString::Format("P%d", pid + 1);
            dc.SetBrush(*wxLIGHT_GREY_BRUSH);
            dc.DrawRectangle(x, y, blockWidth, blockHeight);
            dc.DrawText(label, x + 10, y + 5);
            x +=blockWidth + 5;
        }
    }
};
//Main class
class SchedulerApp : public wxApp {
public:
    bool OnInit() override {
        SchedulerFrame* frame = new SchedulerFrame();
        frame->Show(true);
        return true;
    }
};

wxIMPLEMENT_APP(SchedulerApp);
