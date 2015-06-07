#include <boost/filesystem/operations.hpp>

#include "directory.hh"

namespace bfs = boost::filesystem;
using namespace std;

Directory::Directory() : m_path( bfs::current_path() ) { 
}

Directory::Directory( const char *p ) : m_path(p) { 
}

int Directory::dir_entry_comparator( const Directory::T_DIR_ENTRY &a, const Directory::T_DIR_ENTRY &b ) {
  if( a.is_dir != b.is_dir )
    return a.is_dir > b.is_dir;

  return a.name < b.name;
}

void Directory::scan() { 

  m_entries.clear();

  if ( !bfs::exists( m_path ) ) return;

  bfs::directory_iterator end_itr; // default construction yields past-the-end
  bfs::directory_iterator itr( m_path );

  for( ; itr != end_itr; itr++ ) {

    if( bfs::is_directory( *itr ) ) {

      m_entries.push_back( T_DIR_ENTRY( true, itr->path().filename().string() ));
      continue;
    }

    m_entries.push_back( T_DIR_ENTRY( false, itr->path().filename().string() ));
  }

  m_entries.push_back( T_DIR_ENTRY( true, ".." ));

  sort( m_entries.begin(), m_entries.end(), dir_entry_comparator );

}

int Directory::count() {
  return m_entries.size(); 
}

const Directory::T_DIR_ENTRY & Directory::entry( int i ) const {
  return m_entries[i]; 
}

const string & Directory::path() const {
  return m_path.string();
}

void Directory::cd( const std::string &s ) {

  if( s == ".." ) {
    if( m_path != "/" )
      m_path = m_path.parent_path();
    
  } else {
    m_path /= s;
  }
}
