#pragma once

#include "object.hpp"

namespace jbeau {
    namespace mario {
        class Mario : public jbeau::object::Object {
		private:
			bool alive;
        public:
            Mario();
			void spawn();
			void jump();
			void death();
			
			bool get_is_alive() const;
        };
    }
}