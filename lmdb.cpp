#include <lmdb.h>
#include <string>

int main() {
    // Open the LMDB environment
    MDB_env *env;
    mdb_env_create(&env);
    mdb_env_open(env, "my_lmdb_db", 0, 0664);

    // Start a write transaction
    MDB_txn *txn;
    mdb_txn_begin(env, NULL, 0, &txn);

    // Open the database
    MDB_dbi dbi;
    mdb_dbi_open(txn, NULL, 0, &dbi);

    // Put data
    std::string key = "my_key";
    std::string value = "my_value";
    MDB_val mdb_key, mdb_value;
    mdb_key.mv_data = &key[0];
    mdb_key.mv_size = key.size();
    mdb_value.mv_data = &value[0];
    mdb_value.mv_size = value.size();
    mdb_put(txn, dbi, &mdb_key, &mdb_value, 0);

    // Commit the transaction
    mdb_txn_commit(txn);
 
    // Close the database and environment
    mdb_dbi_close(env, dbi);
    mdb_env_close(env);
    return 0;
}
