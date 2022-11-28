#include <eosio/eosio.hpp>

using namespace eosio;

class [[eosio::contract("system_contract")]] system_contract : public eosio::contract
{

	public:

		using contract::contract;

		/* COSTRUTTORE DEL CONTRATTO */
		system_contract(name receiver, name code, datastream<const char*> ds): contract(receiver, code, ds) {}

	private:

};