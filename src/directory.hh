
#pragma once

#include <boost/filesystem/path.hpp>

#include <vector>
#include <string>

class Directory {
public:

  typedef struct _S_DIR_ENTRY {
    bool is_dir;
    std::string name;

    _S_DIR_ENTRY( bool d, const std::string & n ) { is_dir = d; name = n; }

  } T_DIR_ENTRY, *PT_DIR_ENTRY;

  Directory();
  Directory( const char* );

  static int dir_entry_comparator( const T_DIR_ENTRY&, const T_DIR_ENTRY& );

  void scan(); 
  void cd( const std::string& );
  int count();
  const T_DIR_ENTRY & entry( int ) const;

  const std::string & path() const;

private:

  boost::filesystem::path m_path;

  std::vector<T_DIR_ENTRY> m_entries;
};
