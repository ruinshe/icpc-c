#!/usr/bin/env python3
import scrapy


class ProblemSpider(scrapy.Spider):
    name = 'problemSpider'

    def __init__(self, contestId, problemId,
                 data="data.in", source="main.cc",
                 *args, **kwargs):
        """
        Args:
          contestId: the contest shown in the URL.
          problemId: the problem letter shown in the URL, e.g. A, B, C
          data: data file to store.
        """
        super(ProblemSpider, self).__init__(*args, **kwargs)
        self.start_urls = ['http://codeforces.com/contest/' +
                           contestId + '/problem/' + problemId]
        self.data_in = open(data, "w")
        self.source = open(source, "a")

    def parse(self, response):
        inputs = []
        outputs = []
        for sample in response.css('.sample-test'):
            for item in sample.css('.input'):
                inputs.append('\n'.join(item.css('pre ::text').extract()))
            for item in sample.css('.output'):
                outputs.append('\n'.join(item.css('pre ::text').extract()))

        self.data_in.write('\n\n'.join(inputs))
        self.source.write('/*\nanswer:\n')
        self.source.write('\n'.join(outputs))
        self.source.write('\n*/\n')

    def __del__(self):
        self.data_in.close()
        self.source.close()
