import argparse
import requests
import csv

class MarketDataFetcher:
    def __init__(self, start, end, symbol, timeframe):
        self._columns = {'o': 'Open', 'h': 'High', 'l': 'Low', 'c': 'Close', 'v': 'Volume', 't': 'Timestamp'}
        self._start = start
        self._end = end
        self._symbol = symbol
        self._timeframe = timeframe
    
    def build(self):
        with open(f'../data/{self._symbol.lower()}.csv', 'w', newline='') as df:
            cw = csv.writer(df)
            reached_end = False
            first_page = True
            page_token = ""

            while not reached_end:
                url = f"https://data.alpaca.markets/v1beta3/crypto/us/bars?symbols={self._symbol}/USD&timeframe={self._timeframe}&start={self._start}T00%3A00%3A00Z&end={self._end}T00%3A00%3A00Z&page_token={page_token}&limit=1000&sort=asc"
                response = requests.get(url, headers={"accept": "application/json"}).json()
                ohlc_data = response['bars'][f'{self._symbol}/USD']
                next_page_token = response['next_page_token']

                self._write_to_csv(ohlc_data, cw, first_page)
                page_token = next_page_token
                first_page = False

                if not page_token:
                    reached_end = True
    
    def _write_to_csv(self, ohlc_data, cw, first_page):
        if first_page:
            cw.writerow(self._columns.values())
        
        for row in ohlc_data:
            filtered_row = [row[col] for col in self._columns]
            cw.writerow(filtered_row)

if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('-s', '--start', help='start date for historical data in YYYY-MM-DD', default='2022-01-01')
    parser.add_argument('-e', '--end', help='end date for historical data in YYYY-MM-DD', default='2022-01-30')
    parser.add_argument('-sym', '--symbol', help='Crypto symbol to fetch historical data for e.g. BTC or ETH', default='BTC')
    parser.add_argument('-tf', '--timeframe', help='The frequency of the OHLC data e.g. [1-59]Min, [1-23]Hour, [number]Day, [number]Week, [1-12]Month', default='1Min')
    parser.print_help()

    args = parser.parse_args()
    data_fetcher = MarketDataFetcher(args.start, args.end, args.symbol, args.timeframe)
    data_fetcher.build()