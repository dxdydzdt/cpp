#ifndef __XIO_H__
#define __XIO_H__

#include <iostream>
#include <functional>
#include <map>

namespace xio {
	template<typename T>
	inline T input( const char *const message, std::function<bool( T )> validation = {} ) {
		T result;

		std::cin.clear();

		while ( true ) {
			std::cout << message << std::flush;

			if ( std::cin >> result ) {
				if ( validation && !validation( result ) ) {
					std::cerr << "Введенные данные не соответствуют условию!" << std::endl;

					continue;
				}

				break;
			} else {
				std::cin.clear();
				std::cin.ignore( std::cin.rdbuf()->in_avail(), '\n' );

				std::cerr << "Введены некорректные данные!" << std::endl;

				continue;
			}
		}

		std::cin.ignore( std::cin.rdbuf()->in_avail(), '\n' );
		return result;
	}

	namespace Menu {
		typedef unsigned int ItemId;
		typedef const char *ItemText;
		typedef std::function<void()> ItemHandler;

		struct Item {
		public:
			Item &operator=( const Item &item ) {
				this->text = item.text;
				this->handler = item.handler;

				return *this;
			}

			ItemText text;
			ItemHandler handler;
		};

		typedef std::map<ItemId, Item> Items;

		class Menu {
			Items m_Items;

			inline Menu( Items items ) : m_Items( items ) {}
		public:
			class MenuBuilder {
				Items m_Items;

				inline Item createItem( const char *itemText, std::function<void()> itemHandler = {} ) {
					return Item { itemText, itemHandler };
				}
			public:
				inline MenuBuilder &addItem( const char *itemText, std::function<void()> itemHandler) {
					m_Items[ m_Items.size() ] = createItem( itemText, itemHandler );

					return *this;
				}

				inline Menu *build() {
					addItem( "Выход", nullptr );

					return new Menu( m_Items );
				}
			};

			inline void handle() {
				unsigned int countOfItems = m_Items.size();

				while ( true ) {
					for ( auto item : m_Items ) {
						std::cout
							<< ( item.first + 1 ) << ". "
							<< item.second.text
							<< std::endl;
					}

					unsigned int selectedItem = input<unsigned int>( "Выберите пункт: ", [ &countOfItems ]( unsigned int i ) { return ( i >= 1 && i <= countOfItems ); } );

					if ( selectedItem == countOfItems ) {
						break;
					} else {
						if ( m_Items.at( selectedItem - 1 ).handler ) {
							m_Items.at( selectedItem - 1 ).handler();
						} else {
							std::cout << "Этот пункт ещё не имеет реализации!" << std::endl;
						}

						std::system( "pause" );
						std::system( "cls" );
					}
				}
			}
		};
	}

	inline void pause() {
		std::system( "pause" );
	}
}

#endif // __XIO_H__