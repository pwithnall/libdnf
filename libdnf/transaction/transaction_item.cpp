/*
Copyright (C) 2017-2020 Red Hat, Inc.

This file is part of libdnf: https://github.com/rpm-software-management/libdnf/

Libdnf is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

Libdnf is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with libdnf.  If not, see <https://www.gnu.org/licenses/>.
*/


#include "libdnf/transaction/transaction_item.hpp"

#include "libdnf/transaction/db/repo.hpp"
#include "libdnf/transaction/transaction.hpp"
#include "libdnf/transaction/transaction_item_action.hpp"
#include "libdnf/utils/bgettext/bgettext-lib.h"


namespace libdnf::transaction {


std::string TransactionItem::get_action_name() {
    return TransactionItemAction_get_name(action);
}


std::string TransactionItem::get_action_short() {
    return TransactionItemAction_get_short(action);
}


TransactionItem::TransactionItem(Transaction & trans, Type item_type) : item_type{item_type}, trans{trans} {}


bool TransactionItem::is_forward_action() const {
    return TransactionItemAction_is_forward_action(action);
}


bool TransactionItem::is_backward_action() const {
    return TransactionItemAction_is_backward_action(action);
}


/*
void
TransactionItem::saveReplacedBy()
{
    if (replacedBy.empty()) {
        return;
    }
    const char *sql = "INSERT OR REPLACE INTO item_replaced_by VALUES (?, ?)";
    libdnf::utils::SQLite3::Statement replacedByQuery(trans.get_connection(), sql);
    bool first = true;
    for (const auto &newItem : replacedBy) {
        if (!first) {
            // reset the prepared statement, so it can be executed again
            replacedByQuery.reset();
        }
        replacedByQuery.bindv(get_id(), newItem->get_id());
        replacedByQuery.step();
        first = false;
    }
}

void
TransactionItem::saveState()
{
    const char *sql = R"**(
        UPDATE
          trans_item
        SET
          state = ?
        WHERE
          id = ?
    )**";

    libdnf::utils::SQLite3::Statement query(trans.get_connection(), sql);
    query.bindv(static_cast< int >(get_state()), get_id());
    query.step();
}

void
TransactionItem::dbUpdate()
{
    const char *sql = R"**(
        UPDATE
          trans_item
        SET
          trans_id=?,
          item_id=?,
          repo_id=?,
          action=?,
          reason=?,
          state=?
        WHERE
          id = ?
    )**";

    // try to find an existing repo
    auto query_repo_select_pkg = repo_select_pk_new_query(trans.get_connection());
    auto repo_id = repo_select_pk(*query_repo_select_pkg, get_repoid());

    if (!repo_id) {
        // if an existing repo was not found, insert a new record
        auto query_repo_insert = repo_insert_new_query(trans.get_connection());
        repo_id = repo_insert(*query_repo_insert, get_repoid());
    }


    libdnf::utils::SQLite3::Statement query(trans.get_connection(), sql);
    query.bindv(trans.get_id(),
                getItem()->getId(),
                repo_id,
                static_cast< int >(get_action()),
                static_cast< int >(get_reason()),
                static_cast< int >(get_state()),
                get_id());
    query.step();
}

uint32_t
TransactionItem::getInstalledBy() const {
    return trans.get_user_id();
}
*/


}  // namespace libdnf::transaction