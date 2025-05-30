#include <wx/wx.h>
#include <wx/grid.h>
#include <vector>
#include <thread>
#include <algorithm>


struct Process {
    int id, arrivalTime, burstTime;
    int completionTime = 0, turnaroundTime = 0, waitingTime = 0;
};

class FCFSFrame : public wxFrame {
public:
    FCFSFrame() : wxFrame(nullptr, wxID_ANY, "FCFS-Scheduler", wxDefaultPosition, wxSize(800, 600)) {
        wxPanel* panel = new wxPanel(this);

        wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

        // Table for input/output
        grid = new wxGrid(panel, wxID_ANY);
        grid->CreateGrid(4, 6);
        grid->SetColLabelValue(0, "PID");
        grid->SetColLabelValue(1, "Arrival");
        grid->SetColLabelValue(2, "Burst");
        grid->SetColLabelValue(3, "Completion");
        grid->SetColLabelValue(4, "Turnaround");
        grid->SetColLabelValue(5, "Waiting");

        // Example input
        std::vector<Process> example = {
            {1, 0, 3}, {2, 2, 2}, {3, 4, 4}, {4, 6, 1}
        };
        for (int i = 0; i < example.size(); ++i) {
            grid->SetCellValue(i, 0, wxString::Format("%d", example[i].id));
            grid->SetCellValue(i, 1, wxString::Format("%d", example[i].arrivalTime));
            grid->SetCellValue(i, 2, wxString::Format("%d", example[i].burstTime));
        }

        mainSizer->Add(grid, 1, wxEXPAND | wxALL, 10);

        wxButton* simulateBtn = new wxButton(panel, wxID_ANY, "Run");
        simulateBtn->Bind(wxEVT_BUTTON, &FCFSFrame::OnSimulate, this);
        mainSizer->Add(simulateBtn, 0, wxALIGN_CENTER | wxALL, 15);

        panel->SetSizer(mainSizer);
    }

private:
    wxGrid* grid;

    void OnSimulate(wxCommandEvent&) {
        std::vector<Process> processes;
        for (int i = 0; i < grid->GetNumberRows(); ++i) {
            Process p;
            p.id = wxAtoi(grid->GetCellValue(i, 0));
            p.arrivalTime = wxAtoi(grid->GetCellValue(i, 1));
            p.burstTime = wxAtoi(grid->GetCellValue(i, 2));
            processes.push_back(p);
        }

        // FCFS Simulation (non-realtime)
        std::sort(processes.begin(), processes.end(),
                  [](const Process& a, const Process& b) { return a.arrivalTime < b.arrivalTime; });

        int currentTime = 0;
        for (auto& p : processes) {
            if (p.arrivalTime > currentTime)
                currentTime = p.arrivalTime;

            p.completionTime = currentTime + p.burstTime;
            p.turnaroundTime = p.completionTime - p.arrivalTime;
            p.waitingTime = p.turnaroundTime - p.burstTime;

            currentTime = p.completionTime;
        }

        // Output results
        for (int i = 0; i < processes.size(); ++i) {
            grid->SetCellValue(i, 3, wxString::Format("%d", processes[i].completionTime));
            grid->SetCellValue(i, 4, wxString::Format("%d", processes[i].turnaroundTime));
            grid->SetCellValue(i, 5, wxString::Format("%d", processes[i].waitingTime));
        }
    }
};

class FCFSApp : public wxApp {
public:
    bool OnInit() override {
        FCFSFrame* frame = new FCFSFrame();
        frame->Show(true);
        return true;
    }
};

wxIMPLEMENT_APP(FCFSApp);

