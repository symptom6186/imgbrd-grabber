#ifndef SEARCH_FORMAT_VISITOR_H
#define SEARCH_FORMAT_VISITOR_H

#include <QString>
#include "search/ast/search-visitor.h"
#include "search/search-format.h"
#include "tags/tag-name-format.h"


struct SearchNode;
struct SearchNodeOp;
struct SearchNodeTag;

class SearchFormatVisitor : public SearchVisitor
{
	public:
		SearchFormatVisitor(SearchFormat searchFormat, TagNameFormat tagNameFormat);

		QString run(const SearchNode &node);
		QString error() const;

		void visit(const SearchNodeOp &node) override;
		void visit(const SearchNodeTag &node) override;

	private:
		SearchFormat m_searchFormat;
		TagNameFormat m_tagNameFormat;

		QString m_result;
		QString m_error;
		bool m_inPrecedent = false;
};

#endif // SEARCH_FORMAT_VISITOR_H
