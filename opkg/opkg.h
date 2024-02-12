//
// Created by brant on 2/2/24.
//

#pragma once

#include <stdio.h>
#include <memory>
#include <vector>
#include <string>
#include <map>
#include <ctime>
#include <unordered_set>
using namespace std;
struct package{
    enum InstallState{
        InstallError,
        NotInstalled,
        Installed,
    };
    string Package;
    string Description;
    string Homepage;
    string Version;
    string Section;
    string Maintainer;
    string License;
    string Architecture;
    string Filename;
    string SHA256sum;
    uint Size;
    string Repo;
    string _depends_str;
    vector<shared_ptr<package>> Depends;
    string _recommends_str;
    vector<shared_ptr<package>> Recommends;
    bool autoInstalled;
    long installTime;
    string _status_str;
    InstallState State;
    string Alternatives;
    string _conflicts_str;
    vector<shared_ptr<package>> Conflicts;
    string _replaces_str;
    vector<shared_ptr<package>> Replaces;
    string Conffiles;
    string _provides_str;
    vector<shared_ptr<package>> Provides;
    bool Essential;
};
class opkg {
public:
    void LoadSections(vector<string> *categories){ LoadSections(categories,vector<string>()); }
    void LoadSections(vector<string> *categories, vector<string> excludeRepos);
    void LoadPackages(vector<string> *pVector){ LoadPackages(pVector, vector<string>()); }
    void LoadPackages(vector<string> *pVector, vector<string> excludeRepos);
    void InitializeRepositories();
    void link_dependencies();
    map<string, shared_ptr<package>> packages;
    vector<string> repositories;
    vector<string> sections;
    map<string,unordered_set<string>> sections_by_repo;
    static string FormatPackage(const shared_ptr<package>& package);
private:
    bool parse_line(shared_ptr<package> &ptr, const char *line, bool update);
    bool split_str_and_find(const string& children_str, vector<shared_ptr<package>> &field);
    void update_states();
    void update_lists();
};


