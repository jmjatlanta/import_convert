#include <CSVParser.hpp>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>

/****
 * Convert IB's trade log into TraderVue.com
 * They require it in the format:
 * Date,Time,Symbol,Quantity,Price,Side,Commission,TransFee,ECNFee
 * yyyy-mm-dd,14:01:02,XYZ,100,123.45,SLD,0.43,0.0,0.0,0.0
 */

enum important_columns { Date, Time, Symbol, Quantity, Price, Side, Commission, TransFee, ECNFee, Unknown };

class import_file_parser
{
   public:
   import_file_parser(std::string infile)
   {
      std::ifstream in(infile);
      std::string line;
      bool first_line = true;
      while (std::getline(in, line))
      {
         CSVParser parser(line, ",");
         if (first_line)
         {
            parse_header(parser);
            first_line = false;
         }
         else
         {
            parse_data(parser);
         }
         
      }
   }
   void parse_header(CSVParser& parser)
   {
      for(int i = 0; i < parser.numElements(); ++i)
      {
         std::string name = parser.elementAt(i);
         if (name == "Underlying")
         {
            header_order.push_back(important_columns::Symbol);
            continue;
         }
         if (name == "Action")
         {
            header_order.push_back(important_columns::Side);
            continue;
         }
         if (name == "Quantity")
         {
            header_order.push_back(important_columns::Quantity);
            continue;
         }
         if (name == "Price")
         {
            header_order.push_back(important_columns::Price);
            continue;
         }
         if (name == "Time")
         {
            header_order.push_back(important_columns::Time);
            continue;
         }
         if (name == "Date")
         {
            header_order.push_back(important_columns::Date);
            continue;
         }
         header_order.push_back(important_columns::Unknown);
      }
   }
   std::string parse_text(CSVParser& parser, important_columns col)
   {
      // find out the column number to look for
      for(int i = 0; i < header_order.size(); ++i)
      {
         if (header_order[i] == col)
            return parser.elementAt(i);
      }
      return "";
   }
   void parse_data(CSVParser& parser)
   {
      std::string date = parse_text(parser, important_columns::Date);
      std::string time = parse_text(parser, important_columns::Time);
      std::string symbol = parse_text(parser, important_columns::Symbol);
      std::string quantity = parse_text(parser, important_columns::Quantity);
      std::string price = parse_text(parser, important_columns::Price);
      std::string side = parse_text(parser, important_columns::Side);
      std::string commission = parse_text(parser, important_columns::Commission);
      std::string trans_fee = parse_text(parser, important_columns::TransFee);
      std::string ecn_fee = parse_text(parser, important_columns::ECNFee);
      std::stringstream line;
      line << date << ","
         << time << ","
         << symbol << ","
         << quantity << ","
         << price << ","
         << side << ","
         << commission << ","
         << trans_fee << ","
         << ecn_fee;
      lines_preformatted.push_back(line.str() );
   }
   void save(std::string out_name)
   {
      std::ofstream out(out_name);
      // print header
      out << "Date,Time,Symbol,Quantity,Price,Side,Commission,TransFee,ECNFee\n";
      // print data
      std::for_each(lines_preformatted.begin(), lines_preformatted.end(), [&](std::string line) {
         out << line << "\n";
      });
   }
   std::vector<important_columns> header_order;
   std::vector< std::string > lines_preformatted; 
};

int main(int argc, char** argv)
{
   if (argc != 3)
   {
      std::cerr << "Syntax: " << argv[0] << " in_filename.csv out_filename.csv\n";
      return 0;
   }

   import_file_parser p{ std::string(argv[1]) };
   p.save( std::string(argv[2]));
}