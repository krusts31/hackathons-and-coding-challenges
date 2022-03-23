# mongoexport --help for more explanation.

# -d test -c venmo; this selects database 'test' and collection 'venmo'
# -q '{<json query>}'; this is the query in json format (filter used for finding matching documents)
# -f 'comments'; exports only the 'comments' field and it's values
# --type=csv --noHeaderLine; formats the exported values as "Comma Seperated Values", makes it easier to parse data.


# syntax to get different fields: -f '<field1>.<subfieldOfField1>,<field2>,<field3>'
# example: -f 'comments.count,comments.data.0.message,comments.data.0.display_name'
# you can use the sample.json file from the github to get some ideas of what fields you can use.


# remove --limit=2 to get entire database instead of first 2 entries.
# change -o <fileName> to output to different file

# GET NOTES #
mongoexport -d test -c venmo -f 'payment.note,_id' --type=csv --noHeaderLine -o notes.txt

# GET FIRST COMMENT #
mongoexport -d test -c venmo -q '{"comments.count":1}' -f 'comments.data.0.message,_id' --type=csv --noHeaderLine -o comment_one.txt

# GET SECOND COMMENT
mongoexport -d test -c venmo -q '{"comments.count":2}' -f 'comments.data.1.message,_id' --type=csv --noHeaderLine -o comment_two.txt
 