docs_cnt - количество документов // -3
clnt - результирующая матрицы    // -2
docs - массив документов         // -1

void find_cltn_tf(mtr_t *docs, cltn_t *cltn, size_t docs_cnt)
{
    for (int id = 0; id < docs_cnt; id++)         // 1 
    {
        cltn[id]->n = 0;                          // 2                  
        int word_cnt;                             // 3
        for (int i = 0, k = 0; i < docs[id]->n; i++)   // 4
        {
            if (check_word_in_dict(cltn[id]->buff, 
                  docs[id]->buff[i], 
                  cltn[id]->n))                   // 5
                continue;                         // 6
            word_cnt = 1;                         // 7
            for (int j = i + 1; j < docs[id]->n; j++)  // 8
                if (strcmp(docs[id]->buff[i], 
                    docs[id]->buff[j]) == 0)      // 9
                    word_cnt++;                   // 10

            strcpy(cltn[id]->buff[k].word, 
                   docs[id]->buff[i]);            // 11
            cltn[id]->buff[k].cnt = tf(word_cnt, docs[id]->n); // 12
            cltn[id]->n++;                        // 13
            k++;                                  // 14
        }
    }
}