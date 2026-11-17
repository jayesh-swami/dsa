#include <string>
#include <vector>

using std::string;
using std::vector;

class Solution {
public:
    // O(n): have/need counter
    string minWindow(string s, string t) {
        vector<int> sc(128, 0), tc(128, 0);

        for(char& c: t) tc[c - 'A']++;

        int l = 0, r = 0;
        int resL = 0, resR = s.size() + 1;
        int have = 0, need = 0;

        for(int i = 0; i < tc.size(); i++) {
            if(tc[i]) need++;
        }

        for( ; r < (int) s.size(); r++) {
            int idx = s[r] - 'A';
            sc[idx]++;

            if(tc[idx] && sc[idx] == tc[idx]) have++;

            while(have == need) {
                if(r - l + 1 <= resR - resL + 1) {
                    resR = r;
                    resL = l;
                }
                idx = s[l] - 'A';
                if(tc[idx] && sc[idx] == tc[idx]) have--;
                sc[idx]--;
                l++;
            }
        }

        return resR == s.size() + 1 ? "" : s.substr(resL, resR - resL + 1);
    }

    // O(128·n): full scan of the counts on every check (first accepted version)
    string minWindowScan(string s, string t) {
        vector<int> sc(128, 0), tc(128, 0);

        for(char& c: t) tc[c - 'A']++;

        int l = 0, r = 0;
        int resL = 0, resR = s.size() + 1;

        for( ; r < (int) s.size(); r++) {
            sc[s[r] - 'A']++;
            if(!validWindow(tc, sc)) continue;
            else {
                while(validWindow(tc, sc) && l <= r) {
                    if(r - l + 1 <= resR - resL + 1) {
                        resR = r;
                        resL = l;
                    }
                    sc[s[l] - 'A']--;
                    l++;
                }
            }
        }

        return resR == s.size() + 1 ? "" : s.substr(resL, resR - resL + 1);
    }

    bool validWindow(vector<int>& tc, vector<int>& sc) {
        for(int i = 0; i < (int) tc.size(); i++) {
            if(tc[i] > sc[i]) return false;
        }
        return true;
    }
};
