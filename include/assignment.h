#ifndef ASSIGNMENT_H
#define ASSIGNMENT_H 1

#include <vector>
#include <string>
#include <iostream>

class Assignment {
  private:
    std::vector<short> assignment;

  public:
    Assignment();
    Assignment(int n);
    Assignment(std::vector<short> assignment);
    void set_assignment(std::string s);
    bool is_compatible(const Assignment & partial) const;
    void clear();
    short& operator[] (const int nIndex);
    short operator [] (const int index) const; 
    friend std::ostream& operator<<(std::ostream& out, const Assignment & as);
    friend std::istream& operator>>(std::istream & in, Assignment & as);
    friend bool operator<(const Assignment & lhs, const Assignment & rhs);
    friend bool operator==(const Assignment & lhs, const Assignment & rhs);

    typedef std::vector<short>::iterator iterator;
    typedef std::vector<short>::const_iterator const_iterator;
    iterator begin();
    const_iterator begin() const;
    iterator end();
    const_iterator end() const;
    unsigned int size() const;
};
#endif
