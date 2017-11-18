echo apple && echo bacon || echo jello ; echo pepper #apple bacon pepper
(echo apple && echo bacon) || (echo jello ; echo pepper) #apple bacon
(echo apple)   #apple
((echo ramen) && echo noodles) #ramen noodles
echo chocolate && ((echo chip) || (echo frog || echo goop)) && echo cookies #chocolate chip cookies
((((echo french) || echo beef) ; echo onion) && echo dip) #frencch onion dip
(echo mac && echo and) && echo cheese #(echo grilled cheese) #mac and cheese
echo "((" ; echo "()" ; echo "))" ; ((echo hello) && echo bye)
exit