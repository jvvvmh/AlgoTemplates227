unordered_map<char, vector<char> * > pc;
unordered_map<char, vector<char> * > cp;
set <char> visited;
vector <char> roots;

bool check_circle(char r){
    if (visited.find(r) != visited.end()){
        return true;
    }
    visited.insert(r);
    if (pc.find(r) == pc.end()){
        return false;
    }
    auto ptr = pc[r]; // point to the vector of child
    for (auto i = ptr->begin(); i != ptr->end(); ++i){
        bool has_circle = check_circle(*i);
        if (has_circle) return true;
    }
    return false;
}

string run(char c){
    string res = "(";
    res += c;
    if (pc.find(c) != pc.end()){
        auto ptr = pc[c];
        for (auto i = ptr->begin(); i != ptr->end(); ++i){
            res += run(*i);
        }
    }
    return res + ")";
}

string sExpression(string nodes) {
    stringstream ss;
    ss << nodes;
    string x;
    
    bool other_error = false;
    while(ss >> x){
        char p = x[1], c = x[3];
        if (pc.find(p) != pc.end()){
            pc[p]->push_back(c);
        }else{
            vector<char> * tmp = new vector<char>();
            pc[p] = tmp;
            pc[p]->push_back(c);
        }
        if (cp.find(c) != cp.end()){
            other_error = true;
            cp[c]->push_back(p);
        }else{
            vector<char> * tmp = new vector<char>();
            cp[c] = tmp;
            cp[c]->push_back(p);
        }
    }
    // more than 2 children or duplicate edges
    bool duplicate = false;
    for (auto it = pc.begin(); it != pc.end(); ++it){
        vector<char>* ptr = it->second;
        int size = ptr->size();
        set <char> s;
        for (auto i = ptr->begin(); i != ptr->end(); ++i){
            s.insert(*i);
        }
        int new_size = s.size();
        if (new_size > 2){
            return "E1";
        }
        if (new_size < size){
            duplicate = true;
        }
        ptr->clear();
        ptr->assign(s.begin(), s.end());
        sort(ptr->begin(), ptr->end());
    }
    
    if (duplicate){
        return "E2";
    }
    
    for (auto it = pc.begin(); it != pc.end(); ++it){
        char c = it->first;
        if (cp.find(c) == cp.end()){
            roots.push_back(c);
        }
    }
    
    if (roots.size() == 0){
        return "E3";
    }
    
    bool multiple = roots.size() == 1? false: true;
    for (auto r: roots){
        if (check_circle(r)){
            return "E3";
        }
    }
    if (multiple) return "E4";
    
    if (other_error) return "E5";
    
    string res = run(*roots.begin());
    return res;
}