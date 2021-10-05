from ast import parse
from numpy.lib.utils import source
import pandas as pd
import os

class Pipeline:
    def __init__(self,  ratio, root):
        self.ratio = ratio
        self.root = root
        self.sources = None
        self.train_file_path = None
        self.dev_file_path = None
        self.test_file_path = None
        self.size = None

    # parse source code
    def parse_source(self, query_file):
        # path = self.root+output_file
        # if os.path.exists(path) and option is 'existing':
        #     source = pd.read_pickle(path)
        # else:
        from pycparser import c_parser
        parser = c_parser.CParser()
        source = pd.read_pickle(self.root+query_file)


        source.columns = ['id', 'code', 'name']
        source['code'] = source['code'].apply(parser.parse)

        #     source.to_pickle(path)
        # from pycparser import c_parser
        # parser = c_parser.CParser()
        # source = pd.DataFrame([[1, parser.parse(open(self.root+query_file).read())]])
        # source.columns = ['id', 'code']
        # self.sources = source




        from prepare_data import get_blocks as func
        from gensim.models.word2vec import Word2Vec

        word2vec = Word2Vec.load(self.root+'train/embedding/node_w2v_' + '128').wv
        vocab = word2vec.vocab
        max_token = word2vec.syn0.shape[0]

        def tree_to_index(node):
            token = node.token
            result = [vocab[token].index if token in vocab else max_token]
            children = node.children
            for child in children:
                result.append(tree_to_index(child))
            return result

        def trans2seq(r):
            blocks = []
            func(r, blocks)
            tree = []
            for b in blocks:
                btree = tree_to_index(b)
                tree.append(btree)
            return tree
        trees = source
        # print(trees)
        trees['code'] = trees['code'].apply(trans2seq)
        # print(trees)
        trees.to_pickle(self.root+"query"+'/blocks.pkl')


        return source

    # split data for training, developing and testing
    def split_data(self):
        data = self.sources
        data_num = len(data)
        ratios = [int(r) for r in self.ratio.split(':')]
        train_split = int(ratios[0]/sum(ratios)*data_num)
        val_split = train_split + int(ratios[1]/sum(ratios)*data_num)
        data = data.sample(frac=1, random_state=666)
        train = data.iloc[:train_split] 
        dev = data.iloc[train_split:val_split] 
        test = data.iloc[val_split:] 
        # print(train)

        def check_or_create(path):
            if not os.path.exists(path):
                os.mkdir(path)
        train_path = self.root+'train/'
        check_or_create(train_path)
        self.train_file_path = train_path+'train_.pkl'
        train.to_pickle(self.train_file_path)

        dev_path = self.root+'dev/'
        check_or_create(dev_path)
        self.dev_file_path = dev_path+'dev_.pkl'
        dev.to_pickle(self.dev_file_path)

        test_path = self.root+'test/'
        check_or_create(test_path)
        self.test_file_path = test_path+'test_.pkl'
        test.to_pickle(self.test_file_path)

    # construct dictionary and train word embedding
    def dictionary_and_embedding(self, input_file, size):
        self.size = size
        if not input_file:
            input_file = self.train_file_path
        trees = pd.read_pickle(input_file)
        # print(trees)
        if not os.path.exists(self.root+'train/embedding'):
            os.mkdir(self.root+'train/embedding')
        from prepare_data import get_sequences

        def trans_to_sequences(ast):
            sequence = []
            get_sequences(ast, sequence)
            # print(ast.children())
            return sequence
        corpus = trees['code'].apply(trans_to_sequences)
        # print(len(corpus))
        # for c in corpus:
        #     print(c)
        str_corpus = [''.join(c) for c in corpus]
        # print(len(str_corpus))
        # print((str_corpus))
        trees['code'] = pd.Series(str_corpus, trees.index)
        trees.to_csv(self.root+'train/programs_ns.tsv')
        # print(trees)
        from gensim.models.word2vec import Word2Vec
        w2v = Word2Vec(corpus, size=size, workers=16, sg=1, min_count=3)
        w2v.save(self.root+'train/embedding/node_w2v_' + str(size))

    # generate block sequences with index representations
    def generate_block_seqs(self,data_path,part):
        from prepare_data import get_blocks as func
        from gensim.models.word2vec import Word2Vec

        word2vec = Word2Vec.load(self.root+'train/embedding/node_w2v_' + '128').wv
        vocab = word2vec.vocab
        max_token = word2vec.syn0.shape[0]

        def tree_to_index(node):
            token = node.token
            result = [vocab[token].index if token in vocab else max_token]
            children = node.children
            for child in children:
                result.append(tree_to_index(child))
            return result

        def trans2seq(r):
            blocks = []
            func(r, blocks)
            tree = []
            for b in blocks:
                btree = tree_to_index(b)
                tree.append(btree)
            return tree
        trees = pd.read_pickle(data_path)
        # print(trees)
        trees['code'] = trees['code'].apply(trans2seq)
        # print(trees)
        trees.to_pickle(self.root+part+'/blocks.pkl')

    # run for processing data to train
    def run(self):
        print('parse source code...')
        self.parse_source(query_file='query.pkl')
        # print('split data...')
        # self.split_data()
        # print('train word embedding...')
        # self.dictionary_and_embedding(None,128)
        print('generate block sequences...')
        # self.generate_block_seqs(self.root+'query/', 'query')
        # self.generate_block_seqs(self.dev_file_path, 'dev')
        # self.generate_block_seqs(self.test_file_path, 'test')


ppl = Pipeline('3:1:1', 'data/')
ppl.run()


