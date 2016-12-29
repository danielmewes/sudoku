#ifndef FIELD_H
#define FIELD_H

#include <set>
#include <assert.h>

class Field {
public:
    Field() {
        for (int i = 1; i <= 9; ++i) {
            candidates.insert(i);
        }
    }
    
    bool operator==(const Field &other) const {
        return candidates == other.candidates;
    }
    
    bool operator!=(const Field &other) const {
        return candidates != other.candidates;
    }
    
    void setResolved(int value) {
        candidates.clear();
        candidates.insert(value);
    }

    bool isResolved() const {
        return candidates.size() == 1;
    }
    
    bool hasConflict() const {
        return candidates.empty();
    }

    const std::set<int> &getCandidates() const {
        return candidates;
    }
    
    int getResolved() const {
        assert(isResolved());
        return *candidates.begin();
    }

    void eraseCandidate(int candidate) {
        candidates.erase(candidate);
    }

private:
    std::set<int> candidates;
};

#endif

