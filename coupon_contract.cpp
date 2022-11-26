#include <eosio/eosio.hpp>

using namespace eosio;

class [[eosio::contract("coupon_contract")]] test : public eosio::contract
{

public:

	using contract::contract;

	/* COSTRUTTORE DEL CONTRATTO */
	coupon_contract(name receiver, name code, datastream<const char*> ds):contract(receiver, code, ds) {}

	/* IMPLEMENTAZIONI DELLE ACTION */

	// inserimento coupon
	[[eosio::action]]
	void add_coupon(int coupon_id, std::string pub_id, std::string beerlover_id, int value, std::string exp_date)
	{
		coupon_index coupons(get_self(), get_first_receiver().value);

		// verifica dell'esistenza del coupon nella tabella
		auto c_itr = coupons.find(coupon_id);
		eosio_assert( c_itr != coupons.end() ,"Coupon già presente nel sistema!");

		// verifica della correttezza del campo value del coupon
		if( value<100 && value>0 ){

			// inserimento del record nella tebella
			coupons.emplace(_self, [&](auto& row) {
				row.coupon_id = coupon_id;
				row.pub_id = user_id;
				row.beerlover_id = beerlover_id;
				row.value = value;
				row.exp_date = exp_date;
			});

		} else {
			// errore nel caso di value errata
			eosio_assert( 1 , "Il valore del Coupon è errato!" );
		}	
	}


	// inserimento reward
	[[eosio::action]]
	void add_reward(int reward_id, std::string hash)
	{
		reward_index rewards(get_self(), get_first_receiver().value);

		// verifica dell'esistenza del reward nella tabella
		auto r_itr = rewards.find(reward_id);
		eosio_assert( r_itr != rewards.end() ,"Il Reward di questo Coupon è già presente nel sistema!");

		// inserimento del record all'interno della tabella
		rewards.emplace(_self, [&](auto& row){
			row.reward_id = reward_id;
			row.hash = hash;
		});
	}

	// cancellazione di un coupon
	[[eosio::action]]
	void erase_coupon(int coupon_id)
	{
		coupon_index coupons(get_self(), get_first_receiver().value);
		
		// ricerca del record tramite l'id
		auto c_itr = coupons.find(coupon_id);

		// il record non esiste
		eosio_assert( c_itr != coupons.end() ,"Il Coupon non esiste!");

		// eliminazione del record
		coupons.erase(iterator);
	}

	// cancellazione di un reward
	[[eosio::action]]
	void erase_reward(int coupon_id)
	{
		reward_index rewards(get_self(), get_first_receiver().value);
		
		// ricerca del record tramite l'id
		auto r_itr = rewards.find(reward_id);

		// il record non esiste
		eosio_assert( r_itr != rewards.end() ,"Il Coupon non esiste!");

		// eliminazione del record
		coupons.erase(iterator);
	}



private:

	/* STRUTTURA DEL COUPON */
	struct coupon {
		int coupon_id;
		std::string pub_id;
		std::string beerlover_id;
		int value;
		std::string exp_date;

		int primary_key() const{ return coupon_id;}
	};

	// tabella dei coupons
	using coupon_index = eosio::multi_index<"coupons"_n, coupon>;


	/* STRUTTURA DEL REWARD */
	struct reward {
		int reward_id;
		std::string hash;
	};

	// tabella dei rewards
	using reward_index = eosio::multi_index<"rewards"_n, reward>;

}