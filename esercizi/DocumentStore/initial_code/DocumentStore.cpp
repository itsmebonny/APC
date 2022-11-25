#include "DocumentStore.h"

DocumentStore::DocumentStore (std::size_t s):
    docs(std::vector<Document>(s)), docsDraft(std::vector<Document>(DRAFT_SIZE)), size(s), curr(0), currDraft(0)
{}

DocumentStore::DocumentStore(DocumentStore &pippo):docs(pippo.docs), docsDraft(pippo.docsDraft), size(pippo.size), curr(pippo.curr), currDraft(0){};

DocumentStore DocumentStore::operator= (DocumentStore &pippo){
    docs = pippo.docs;
    size = pippo.size;
    curr = pippo.curr;
    currDraft = 0;
    return *this;
}


void DocumentStore::addDocument (const Document& doc)
{
    if (curr < size)
        docs[curr++] = doc;
}

void DocumentStore::saveAsDraft (const Document& draft)
{
    if (currDraft < DRAFT_SIZE)
        docsDraft[currDraft++] = draft;
}

void DocumentStore::print () const
{
    std::cout << "List of Documents:" << std::endl;
    for (std::size_t j = 0; j < curr; ++j)
        docs[j].print();

    std::cout << "List of Drafts:" << std::endl;
    for (std::size_t j = 0; j < currDraft; ++j)
        docsDraft[j].print();
}
