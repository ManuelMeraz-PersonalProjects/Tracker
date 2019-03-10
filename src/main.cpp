#include <soci-sqlite3.h>
#include <soci.h>

int main() {
  soci::session db("sqlite3", "db=test.db timeout=2 shared_cache=true");
  int i = 7;
  int j = 8;
  db << "insert into table(x, y) values(?, ?)", soci::use(i), soci::use(j);
}
